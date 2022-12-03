#include "DungeonGenerator.h"
#include "../../utils/RandomNumberGenerator.h"
#include "../algorithms/CoordinatesConverter.h"
#include "../algorithms/astar/AStar.h"
#include "SFML/Graphics/CircleShape.hpp"

DungeonGenerator::DungeonGenerator(const std::list<Room>& mRooms)
{
}

GeneratedMap DungeonGenerator::procedurallyGenerateMap()
{
    generateRooms();
    triangulation();
    minSpanningTree();
    createHallways();

    return mGeneratedMap;
}

void DungeonGenerator::generateRooms()
{
    RoomGenerator generator(mGeneratedMap);
    mRooms = generator.allocateRooms();
}

void DungeonGenerator::triangulation()
{
    mTriangleEdges = mDelaunayTriangulation.triangulation(mRooms);
}

void DungeonGenerator::minSpanningTree()
{
    copyTriangleEdgesToMst();
    mMST.processMST(mFinalEdges);
    addRandomEdgesToMst();
}

void DungeonGenerator::createHallways()
{
    AStar pathFinder(mGeneratedMap);
    for (auto& edge: mFinalEdges)
    {

        pathFinder.generateHallway(
            converter::worldCoordinateToTileCoordinate<int>(edge.mVertexA.x, edge.mVertexA.y),
            converter::worldCoordinateToTileCoordinate<int>(edge.mVertexB.x, edge.mVertexB.y));
    }

#if DEBUG
    for (auto point: mGeneratedMap)
    {
        for (auto point2: point)
        {
            std::cout << point2 << " ";
        }
        std::cout << std::endl;
    }
#endif
}

void DungeonGenerator::drawDebugLines(sf::RenderWindow* window)
{
    mMST.draw(window, mFinalEdges);
    drawCenterOfTheRoom(window);
#if DEBUG

#endif
}
void DungeonGenerator::drawCenterOfTheRoom(sf::RenderWindow* window)
{
    sf::CircleShape shape(2);
    shape.setFillColor(sf::Color(100, 250, 50));
    std::list<Room>::iterator it;
    for (it = mRooms.begin(); it != mRooms.end(); ++it)
    {
        shape.setPosition(it->mCenter);
        window->draw(shape);
    }
}

void DungeonGenerator::copyTriangleEdgesToMst()
{
    std::set<Edge>::iterator itr;
    for (itr = mTriangleEdges.begin(); itr != mTriangleEdges.end(); itr++)
    {
        mFinalEdges.push_back(*itr);
    }
}

void DungeonGenerator::addRandomEdgesToMst()
{
    std::set<Edge> notAddedEdges = mTriangleEdges;
    std::set<Edge> mstUniqueEdges;
    std::set<Edge> result;
    float chanceOfAddingEdge{20.f};

    storeUniqueEdges(mstUniqueEdges);

    for (auto edge: notAddedEdges)
    {
        if (!mstUniqueEdges.contains(edge) &&
            (generateFloatNumberInRange(0.f, 1.f) * 100 < chanceOfAddingEdge))
        {
            mFinalEdges.push_back(edge);
        }
    }
}
void DungeonGenerator::storeUniqueEdges(std::set<Edge>& addedEdges)
{
    for (auto edge: mFinalEdges)
    {
        addedEdges.emplace(edge);
    }
}
