#ifndef TERRAINGENERATOR_H
#define TERRAINGENERATOR_H

#include "../../utils/RandomNumberGenerator.h"
#include <poly2tri/poly2tri.h>
#include "Tile.h"
#include "Room.h"
#include "SFML/Graphics/VertexArray.hpp"
#include "MinSpanningTree.h"
#include <functional>

using RoomGrid = std::vector<std::vector<int>>;
using GeneratedMap = std::array<std::array<int, 32>, 32>;

class Map;

class TerrainGenerator
{
    enum RoomTypes
    {
        CELLULAR_AUTOMATA = 0,
        RECTANGLE,
        CIRCLE
    };

    enum CellType
    {
        ROOM = 0,
        HALL,
        NONE
    };

public:
    TerrainGenerator() = default;

    explicit TerrainGenerator(const std::list<Room>& mRooms);

    ~TerrainGenerator() = default;

    std::vector<std::vector<int>> generateRoom();

    GeneratedMap procedurallyGenerateMap();

    void draw(sf::RenderWindow* window);

private:
    bool isRoomColliding(Room& temp);

    RoomGrid generateRoomRectangle();

    RoomGrid getMultiDimGrid(int width, int height, int value);

    void generateRoomCA();

    void generateRoomCircle();

    bool placeRoomOnMap(std::vector<std::vector<int>> room);

    /**
     * @brief Randomly allocate some number of rooms on the map
     */
    void allocateRooms();

    /**
     * @brief Create Delaunay triangulation map from center of each room.
     * This creates many connections between nearby points.
     */
    void triangulation();

    void populateLinesVertexArray();

    void populateTrianglesVertexArray(const std::vector<p2t::Triangle*>& triangulatedFigure);

    sf::Vector2f getCenter();

    void minSpanningTree();

    void sortRoomsCoordinatesClockwiseOrder();

    std::vector<p2t::Triangle*> handleTriangulation();

    void populateMSTVertexArray();

private:
    sf::VertexArray delaunayEdges; //< Triangles (consisting of vertexes) building the current figure.

    std::list<Room> mRooms;
    std::set<Edge> mTriangleEdges;
    std::vector<Edge> mMinSpanningTreeEdges;

    sf::VertexArray triangleLines;
    sf::VertexArray mstLines;

    std::vector<p2t::Point*> polyline;
    GeneratedMap mGeneratedMap{ 0 };
    int rooms{ 0 };
};

#endif //TERRAINGENERATOR_H
