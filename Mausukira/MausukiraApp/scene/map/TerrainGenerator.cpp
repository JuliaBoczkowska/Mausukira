#include "TerrainGenerator.h"
#include "SFML/Graphics/CircleShape.hpp"
#include <iostream>
#include <math.h>

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
    std::cout << "MADE " << rooms << " ROOMS" << std::endl;
    return mGeneratedMap;
}

void TerrainGenerator::allocateRooms()
{
    int count = 0;
    while (count != 5)
    {
        count++;
//    while (true)
//    {
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
    triangles.setPrimitiveType(sf::Triangles);
    lines.setPrimitiveType(sf::Lines);

    Room::setCenter(getCenter());
    mRooms.sort([](Room first, Room second)
    {
        double a1 =
            (static_cast<int>(
                 atan2(first.mCenter.x - Room::centerOfAllPoints.x, first.mCenter.y - Room::centerOfAllPoints.y) *
                 (180.0 / 3.141592653589793238463)) + 360) %
            360;
        double a2 =
            (static_cast<int>(
                 atan2(second.mCenter.x - Room::centerOfAllPoints.x, second.mCenter.y - Room::centerOfAllPoints.y) *
                 (180.0 / 3.141592653589793238463)) + 360) % 360;
        return a1 < a2;
    });


    std::list<Room>::iterator it;
    for (it = mRooms.begin(); it != mRooms.end(); ++it)
    {
        std::cout << "ROOM CENTER IS: { " << it->mCenter.x << " , " << it->mCenter.y << " }" << std::endl;
        polyline.push_back(new p2t::Point(it->mCenter.x, it->mCenter.y));
    }

    p2t::CDT cdt(polyline);
    cdt.Triangulate();
    const auto triangulatedFigure = cdt.GetTriangles();
    triangles.resize(triangulatedFigure.size() * 3);
    lines.resize(triangulatedFigure.size() * 3 * 3);

    populateTrianglesVertexArray(triangulatedFigure);
    populateLinesVertexArray();
}

void TerrainGenerator::populateTrianglesVertexArray(const std::vector<p2t::Triangle*>& triangulatedFigure)
{
    size_t arrayIndex = 0;
    for (auto* triangulatedTriangle: triangulatedFigure)
    {
        for (size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex)
        {
            triangles[arrayIndex] = sf::Vertex(
                sf::Vector2f(triangulatedTriangle->GetPoint(vertexIndex)->x,
                    triangulatedTriangle->GetPoint(vertexIndex)->y));
            ++arrayIndex;
        }
    }
}

void TerrainGenerator::populateLinesVertexArray()
{
    for (int arrayIndex = 0, vertexIndex = 0; vertexIndex < triangles.getVertexCount();)
    {
        auto first = vertexIndex;
        auto second = vertexIndex + 1;
        auto third = vertexIndex + 2;
        vertexIndex = vertexIndex + 3;

        // 1 -> 2 triangle edge
        lines[arrayIndex] = sf::Vertex(
            sf::Vector2f(triangles[first].position.x, triangles[first].position.y));
        lines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(triangles[second].position.x, triangles[second].position.y));

        // 1 -> 3 triangle edge
        lines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(triangles[first].position.x, triangles[first].position.y));
        lines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(triangles[third].position.x, triangles[third].position.y));

        // 2 -> 3 triangle edge
        lines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(triangles[second].position.x, triangles[second].position.y));
        lines[++arrayIndex] = sf::Vertex(
            sf::Vector2f(triangles[third].position.x, triangles[third].position.y));
        ++arrayIndex;
    }

    for (int arrayIndex = 0; arrayIndex < lines.getVertexCount(); ++arrayIndex)
    {
        lines[arrayIndex].color = sf::Color::Green;
    }
}

RoomGrid TerrainGenerator::generateRoom()
{
    // TODO complete switch
    RoomTypes roomType = RECTANGLE;

    switch (roomType)
    {
        case RECTANGLE:return generateRoomRectangle();
//            break;
//        case CELLULAR_AUTOMATA:generateRoomCA();
//            break;
//        case CIRCLE:generateRoomCircle();
//            break;
    }
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

bool TerrainGenerator::placeRoomOnMap(std::vector<std::vector<int>> room)
{
    rooms++;

    Room temp;
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
        sf::Vector2i location = generateTwoNumbersInRange(1, 30);
        roomRow = static_cast<int>(room.size());
        roomCol = static_cast<int>(room.at(0).size());

        /** Center of the room */
        sf::Vector2f center = sf::Vector2f(
            { static_cast<float>((location.x * (TILE_SIZE * 2)) + ((roomRow * TILE_SIZE * 2) / 2)),
              static_cast<float>((location.y * (TILE_SIZE * 2)) + ((roomCol * TILE_SIZE * 2) / 2)) });

        /** Additional one is added in order to obtain space between rooms */
        temp = Room(location, sf::Vector2i{ roomRow + 1, roomCol + 1 }, room, center);
        ++count;
    }
    while (isRoomColliding(temp));

    mRooms.push_back(temp);

    int index = 0;

    for (int i = temp.mLocation.x; i < mGeneratedMap.size() && (i < (temp.mLocation.x + roomRow)); ++i)
    {
        for (int j = temp.mLocation.y;
             j < mGeneratedMap.size() && (j < (temp.mLocation.y + roomCol)); ++j)
        {
//            TODO Solution for circle and CA. For square only value "1" is sufficient
//            temp_row = index % roomRow;
//            temp_col = index / roomRow;

            mGeneratedMap[i][j] = 1;
            index++;
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
    window->draw(lines);
}
