#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "../algorithms/mst/MinSpanningTree.h"
#include "../algorithms/triangulation/DelaunayTriangulation.h"
#include "Room.h"
#include "RoomGenerator.h"
#include "SFML/Graphics/VertexArray.hpp"
#include "Tile.h"
#include <functional>

class Map;
enum CellType
{
    NONE = 0,
    ROOM = 1,
    HALL = 2,
    //    WALL = 3,
};

class DungeonGenerator
{
public:
    DungeonGenerator() = default;
    explicit DungeonGenerator(const std::list<Room>& mRooms);
    ~DungeonGenerator() = default;

    std::array<std::array<int, 32>, 32> procedurallyGenerateMap();
    void drawDebugLines(sf::RenderWindow* window);

private:
    /**
     * @brief Create Delaunay triangulation map from center of each room.
     * This creates many connections between nearby points.
     */
    void triangulation();
    void minSpanningTree();
    void populateMSTVertexArray();
    void addRandomEdgesToMst();
    void createHallways();
    void generateRooms();

private:
    std::list<Room> mRooms;
    std::vector<Edge> mFinalEdges;
    std::set<Edge> mTriangleEdges;
    MinSpanningTree mMST;
    DelaunayTriangulation mDelaunayTriangulation;

    std::array<std::array<int, 32>, 32> mGeneratedMap{0};
    void drawCenterOfTheRoom(sf::RenderWindow* window);
    void copyTriangleEdgesToMst();
    void storeUniqueEdges(std::set<Edge>& addedEdges);
};

#endif// DUNGEONGENERATOR_H
