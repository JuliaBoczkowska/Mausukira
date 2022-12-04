#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "../algorithms/mst/MinSpanningTree.h"
#include "../algorithms/triangulation/DelaunayTriangulation.h"
#include "MapContext.h"
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
};

class DungeonGenerator
{
    using Rooms = std::list<Room>;
    using Edges = std::vector<Edge>;
    using UniqueEdges = std::set<Edge>;

public:
    DungeonGenerator(MapContext& mapContext);
    ~DungeonGenerator() = default;

    void procedurallyGenerateMap();
    void drawDebugLines(sf::RenderWindow& window);
    sf::Vector2f getCenterOfTheFirstRoom();

private:
    /**
     * @brief Create Delaunay triangulation map from center of each room.
     * This creates many connections between nearby points.
     */
    void triangulation();
    void minSpanningTree();
    void addRandomEdgesToMst();
    void createHallways();
    void generateRooms();
    void drawCenterOfTheRoom(sf::RenderWindow& window);
    void copyTriangleEdgesToMst();
    void storeUniqueEdges(UniqueEdges& addedEdges);

private:
    Rooms mRooms;
    MinSpanningTree mMST;
    DelaunayTriangulation mDelaunayTriangulation;
    MapContext& mMapContext;

    Edges mFinalEdges;
    UniqueEdges mTriangleEdges;
};

#endif// DUNGEONGENERATOR_H
