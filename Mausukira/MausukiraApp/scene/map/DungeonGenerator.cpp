#include "DungeonGenerator.h"
#include "../../utils/RandomNumberGenerator.h"
#include "../Debug.h"
#include "../algorithms/CoordinatesConverter.h"
#include "../algorithms/astar/AStar.h"
#include "SFML/Graphics/CircleShape.hpp"

DungeonGenerator::DungeonGenerator(MapContext& mapContext)
    : mMapContext(mapContext)
{
}

void DungeonGenerator::procedurallyGenerateMap()
{
    generateRooms();
    triangulation();
    minSpanningTree();
    createHallways();

    updateCenterOfTheFirstRoom();
}

void DungeonGenerator::generateRooms()
{
    RoomGenerator generator(mMapContext.mMap);
    mRooms = generator.allocateRooms();
}

void DungeonGenerator::triangulation()
{
    mTriangleEdges = mDelaunayTriangulation.triangulation(mRooms);
}

void DungeonGenerator::minSpanningTree()
{
    copyTriangleEdgesToMst();
    mFinalEdges = mMinSpanningTree.processMST(mFinalEdges);
    addRandomEdgesToMst();
}

void DungeonGenerator::createHallways()
{
    AStar pathFinder(mMapContext.mMap);
    for (auto& edge: mFinalEdges)
    {

        pathFinder.generateHallway(
            converter::worldCoordinateToTileCoordinate<int>(edge.mVertexA.x, edge.mVertexA.y),
            converter::worldCoordinateToTileCoordinate<int>(edge.mVertexB.x, edge.mVertexB.y));
    }
#if DEBUG_ROOM_GENERATION
    for (auto point: mMapContext.mMap)
    {
        for (auto point2: point)
        {
            std::cout << point2 << " ";
        }
        std::cout << std::endl;
    }
#endif
}

void DungeonGenerator::drawDebugLines(sf::RenderWindow& window)
{
#if DEBUG_ROOM_GENERATION
    mDelaunayTriangulation.draw(window);
    mMinSpanningTree.draw(window);
    drawRoomCenter(window);
#endif
}

void DungeonGenerator::drawRoomCenter(sf::RenderWindow& window)
{
    std::list<Room>::iterator it;
    for (it = mRooms.begin(); it != mRooms.end(); ++it)
    {
        it->draw(window);
    }
}

void DungeonGenerator::copyTriangleEdgesToMst()
{
    UniqueEdges::iterator itr;
    for (itr = mTriangleEdges.begin(); itr != mTriangleEdges.end(); itr++)
    {
        mFinalEdges.push_back(*itr);
    }
}

void DungeonGenerator::addRandomEdgesToMst()
{
    UniqueEdges notAddedEdges = mTriangleEdges;
    UniqueEdges mstUniqueEdges;
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
    mMinSpanningTree.setMstEdges(mFinalEdges);
}

void DungeonGenerator::storeUniqueEdges(UniqueEdges& addedEdges)
{
    for (auto edge: mFinalEdges)
    {
        addedEdges.emplace(edge);
    }
}
void DungeonGenerator::updateCenterOfTheFirstRoom()
{
    mMapContext.centerOfTheFirstRoom = mRooms.begin()->mCenter;
}
