#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "SFML/Graphics/VertexArray.hpp"
#include "dungeon/algorithms/mst/MinSpanningTree.h"
#include "dungeon/algorithms/triangulation/DelaunayTriangulation.h"
#include "dungeon/map/CellType.h"
#include "dungeon/map/MapContext.h"
#include "dungeon/map/Tile/Tile.h"
#include "dungeon/map/room/Room.h"
#include "dungeon/map/room/RoomGenerator.h"
#include <functional>

class Map;

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

    void drawRoomCenter(sf::RenderWindow& window);

    void copyTriangleEdgesToMst();

    void storeUniqueEdges(UniqueEdges& addedEdges);

private:
    Rooms mRooms;
    RoomGenerator mRoomGenerator;
    MinSpanningTree mMinSpanningTree;
    DelaunayTriangulation mDelaunayTriangulation;
    MapContext& mMapContext;

    Edges mFinalEdges;
    UniqueEdges mTriangleEdges;
};

#endif// DUNGEONGENERATOR_H
