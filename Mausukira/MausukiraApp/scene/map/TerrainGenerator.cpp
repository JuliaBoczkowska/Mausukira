#include "TerrainGenerator.h"
#include "../../utils/RandomNumberGenerator.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "../algorithms/CoordinatesConverter.h"
#include "../astar/AStar.h"
#include <iostream>

static constexpr auto PI = 3.141592653589793238463;

TerrainGenerator::TerrainGenerator(const std::list<Room>& mRooms)
    : mRooms(mRooms)
{
}

RoomGrid TerrainGenerator::getMultiDimGrid(int width, int height, int value = CellType::ROOM)
{
    std::vector<int> row(height, value);
    std::vector<std::vector<int>> grid(width, row);
    return grid;
}

GeneratedMap TerrainGenerator::procedurallyGenerateMap()
{
    allocateRooms();
    triangulation();
    minSpanningTree();
    createHallways();
    std::cout << "MADE " << roomCounter << " ROOMS" << std::endl;
    return mGeneratedMap;
}

void TerrainGenerator::allocateRooms()
{
//    int count = 0;
//    while (count != 5)
//    {
//        count++;
    while (true)
    {
        if (!placeRoomOnMap(generateRoom()))
        {
            break;
        }
    }
}

sf::Vector2f TerrainGenerator::getCenter()
{
    int x = 0;
    int y = 0;
    for (auto room: mRooms)
    {
        x += room.mCenter.x;
        y += room.mCenter.y;
    }
    sf::Vector2f center{ 0, 0 };
    center.x = x / mRooms.size();
    center.y = y / mRooms.size();
    return center;
}

void TerrainGenerator::triangulation()
{
    delaunayEdges.setPrimitiveType(sf::Triangles);
    triangleLines.setPrimitiveType(sf::Lines);

    sortRoomsCoordinatesClockwiseOrder();

    std::list<Room>::iterator it;
    for (it = mRooms.begin(); it != mRooms.end(); ++it)
    {
        std::cout << "ROOM CENTER IS: { " << it->mCenter.x << " , " << it->mCenter.y << " }" << std::endl;
        polyline.push_back(new p2t::Point(it->mCenter.x, it->mCenter.y));
    }

    p2t::CDT cdt(polyline);
    cdt.Triangulate();
    const auto triangulatedFigure = cdt.GetTriangles();

    delaunayEdges.resize(triangulatedFigure.size() * 3);
    triangleLines.resize(triangulatedFigure.size() * 3 * 3);

    populateTrianglesVertexArray(triangulatedFigure);
    populateLinesVertexArray();
}

void TerrainGenerator::sortRoomsCoordinatesClockwiseOrder()
{
    Room::setCenter(getCenter());
    mRooms.sort([](Room first, Room second)
    {
        double a1 =
            (static_cast<int>(
                 atan2(first.mCenter.x - Room::centerOfAllPoints.x, first.mCenter.y - Room::centerOfAllPoints.y) *
                 (180.0 / PI)) + 360) %
            360;
        double a2 =
            (static_cast<int>(
                 atan2(second.mCenter.x - Room::centerOfAllPoints.x, second.mCenter.y - Room::centerOfAllPoints.y) *
                 (180.0 / PI)) + 360) % 360;
        return a1 < a2;
    });
}

void TerrainGenerator::populateTrianglesVertexArray(const std::vector<p2t::Triangle*>& triangulatedFigure)
{

    for (auto* triangulatedTriangle: triangulatedFigure)
    {
        mTriangleEdges.emplace(
            Edge(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x, triangulatedTriangle->GetPoint(0)->y),
                sf::Vector2i(triangulatedTriangle->GetPoint(1)->x, triangulatedTriangle->GetPoint(1)->y)));

        mTriangleEdges.emplace(
            Edge(sf::Vector2i(triangulatedTriangle->GetPoint(1)->x, triangulatedTriangle->GetPoint(1)->y),
                sf::Vector2i(triangulatedTriangle->GetPoint(2)->x, triangulatedTriangle->GetPoint(2)->y)));

        mTriangleEdges.emplace(
            Edge(sf::Vector2i(triangulatedTriangle->GetPoint(0)->x, triangulatedTriangle->GetPoint(0)->y),
                sf::Vector2i(triangulatedTriangle->GetPoint(2)->x, triangulatedTriangle->GetPoint(2)->y)));
    }

    size_t arrayIndex = 0;
    for (auto* triangulatedTriangle: triangulatedFigure)
    {
        for (size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex)
        {
            delaunayEdges[arrayIndex] = sf::Vertex(
                sf::Vector2f(triangulatedTriangle->GetPoint(vertexIndex)->x,
                    triangulatedTriangle->GetPoint(vertexIndex)->y));
            ++arrayIndex;
        }
    }
}

void TerrainGenerator::populateLinesVertexArray()
{
    for (int arrayIndex = 0, vertexIndex = 0; vertexIndex < delaunayEdges.getVertexCount();)
    {
        auto first = vertexIndex;
        auto second = vertexIndex + 1;
        auto third = vertexIndex + 2;
        vertexIndex = vertexIndex + 3;

        // 1 -> 2 triangle edge
        triangleLines[arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[first].position.x, delaunayEdges[first].position.y));
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[second].position.x, delaunayEdges[second].position.y));

        // 1 -> 3 triangle edge
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[first].position.x, delaunayEdges[first].position.y));
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[third].position.x, delaunayEdges[third].position.y));

        // 2 -> 3 triangle edge
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[second].position.x, delaunayEdges[second].position.y));
        triangleLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(delaunayEdges[third].position.x, delaunayEdges[third].position.y));
        ++arrayIndex;
    }

    for (int arrayIndex = 0; arrayIndex < triangleLines.getVertexCount(); ++arrayIndex)
    {
        triangleLines[arrayIndex].color = sf::Color::Green;
    }
}

void TerrainGenerator::populateMSTVertexArray()
{
    for (int arrayIndex = 0, vertexIndex = 0; vertexIndex < mMinSpanningTreeEdges.size(); ++vertexIndex, ++arrayIndex)
    {
        mstLines[arrayIndex] = sf::Vertex(
            sf::Vector2f(mMinSpanningTreeEdges[vertexIndex].mVertexA.x, mMinSpanningTreeEdges[vertexIndex].mVertexA.y));
        mstLines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(mMinSpanningTreeEdges[vertexIndex].mVertexB.x,
                mMinSpanningTreeEdges[vertexIndex].mVertexB.y));;
    }

    for (int vertexIndex = 0; vertexIndex < mstLines.getVertexCount(); ++vertexIndex)
    {
        mstLines[vertexIndex].color = sf::Color::Blue;
    }
}

RoomGrid TerrainGenerator::generateRoom()
{
    // TODO complete switch
    RoomTypes roomType = RECTANGLE;

    switch (roomType)
    {
        case RECTANGLE:return generateRoomRectangle();
            break;
//        case CELLULAR_AUTOMATA:generateRoomCA();
//            break;
//        case CIRCLE:generateRoomCircle();
//            break;
    }
    return generateRoomRectangle();
}

std::vector<std::vector<int>> TerrainGenerator::generateRoomRectangle()
{
    const auto& [width, height] = generateTwoNumbersInRange(4, 7);
    auto grid = getMultiDimGrid(width, height);

    return grid;
}

void TerrainGenerator::generateRoomCA()
{

}

void TerrainGenerator::generateRoomCircle()
{

}

bool TerrainGenerator::placeRoomOnMap(std::vector<std::vector<int>> roomOutline)
{
    /** Counter for debug purposes */
    roomCounter++;

    Room roomToBeAdded;
    int count = 0;
    int roomRow{ 0 };
    int roomCol{ 0 };

    do
    {
        /** After some number of attempts leave */
        if (count == 10000)
        {
            return false;
        }
        sf::Vector2i tileLocation = generateTwoNumbersInRange(1, 30);
        roomRow = roomOutline.size();
        roomCol = roomOutline.at(0).size();


        if ((tileLocation.x + roomRow) > 32)
        {
            roomRow = 32 - tileLocation.x;
        }

        if ((tileLocation.y + roomCol) > 32)
        {
            roomCol = 32 - tileLocation.y;
        }

        auto worldLocation = converter::tileToWorldCoordinate<float>(tileLocation.x, tileLocation.y);
        auto worldRoomDimension = converter::tileToWorldCoordinate<float>(roomRow, roomCol);


        /** Center of the room */
        sf::Vector2f center = (worldLocation + (worldRoomDimension / 2.f));

        /** Additional one is added in order to obtain space between rooms */
        roomToBeAdded = Room(tileLocation, sf::Vector2i{ roomRow + 1, roomCol + 1 }, roomOutline, center);
        ++count;
    }
    while (isRoomColliding(roomToBeAdded));

    mRooms.push_back(roomToBeAdded);

//    int index = 0;

    for (int i = roomToBeAdded.mLocation.x;
         i < mGeneratedMap.size() && (i < (roomToBeAdded.mLocation.x + roomRow)); ++i)
    {
        for (int j = roomToBeAdded.mLocation.y;
             j < mGeneratedMap.size() && (j < (roomToBeAdded.mLocation.y + roomCol)); ++j)
        {
//            TODO Solution for circle and CA. For square only value "1" is sufficient
//            temp_row = index % roomRow;
//            temp_col = index / roomRow;

            mGeneratedMap[i][j] = CellType::ROOM;
//            index++;
        }
    }
    return true;
}

bool TerrainGenerator::isRoomColliding(Room& temp)
{
    for (auto& room: mRooms)
    {
        if (room.collide(temp))
        {
            return true;
        }
    }
    return false;
}

void TerrainGenerator::draw(sf::RenderWindow* window)
{
    // dots
    sf::CircleShape shape(2);
    shape.setFillColor(sf::Color(100, 250, 50));

    // rooms
    std::list<Room>::iterator it;
    for (it = mRooms.begin(); it != mRooms.end(); ++it)
    {
        shape.setPosition(it->mCenter);
        window->draw(shape);
    }

    // triangles
    //window->draw(triangles);
    window->draw(triangleLines);
    window->draw(mstLines);
}

void TerrainGenerator::minSpanningTree()
{
    std::set<Edge>::iterator itr;
    for (itr = mTriangleEdges.begin(); itr != mTriangleEdges.end(); itr++)
    {
        mMinSpanningTreeEdges.push_back(*itr);
    }

    mMinSpanningTreeEdges = MinSpanningTree::processMST(mMinSpanningTreeEdges);
    addMoreEdgesToMap();

    /** Drawing process */
    mstLines.setPrimitiveType(sf::Lines);
    mstLines.resize(mMinSpanningTreeEdges.size() * 2);
    populateMSTVertexArray();
}

void TerrainGenerator::addMoreEdgesToMap()
{
    std::set<Edge> notAddedEdges = mTriangleEdges;
    std::set<Edge> addedEdges;
    std::set<Edge> result;

    float chanceOfAddingEdge{ 20.f };

    for (auto edge: mMinSpanningTreeEdges)
    {
        addedEdges.emplace(edge);
    }

    for (auto edge: notAddedEdges)
    {
        if (!addedEdges.contains(edge) && (generateFloatNumberInRange(0.f, 1.f) * 100 < chanceOfAddingEdge))
        {
            mMinSpanningTreeEdges.push_back(edge);
        }
    }
}

void TerrainGenerator::createHallways()
{
    AStar pathFinder(mGeneratedMap);

    for (auto point: mGeneratedMap)
    {
        for (auto point2: point)
        {
            std::cout << point2 << " ";
        }
        std::cout << std::endl;
    }

    for (auto& edge: mMinSpanningTreeEdges)
    {

        pathFinder.generateHallway(
            converter::worldCoordinateToTileCoordinate<int>(edge.mVertexA.x, edge.mVertexA.y),
            converter::worldCoordinateToTileCoordinate<int>(edge.mVertexB.x, edge.mVertexB.y));
    }
}
