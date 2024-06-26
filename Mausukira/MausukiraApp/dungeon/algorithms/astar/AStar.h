#ifndef ASTAR_H
#define ASTAR_H

#include "AStarHelper.h"
#include "dungeon/map/Constants.h"
#include <map>
#include <unordered_map>

enum CellType;
using GeneratedMap = std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y>;

class AStar
{
public:
    AStar(GeneratedMap& map);

    GeneratedMap generateHallway(const sf::Vector2i& startingPoint, const sf::Vector2i& finalPoint);

private:
    void updateMapAroundTile(const sf::Vector2i& centerOfTileCoordinates, const PathCost& cost);

    void checkTilesAround(const sf::Vector2i& tile, const PathCost& costOfTile);

    void drawFinalPathOnMap(const sf::Vector2i& lastHandledTile);

    void setOnMapTileType(const sf::Vector2i& tile, CellType type);

    void reInitializeAlgorithm();

private:
    sf::Vector2i mStartPoint;
    sf::Vector2i mFinalPoint;

    std::unordered_map<as::helper::Coordinate, PathCost> mVisitedTiles;
    std::multimap<PathCost, sf::Vector2i> mUnvisitedTiles;

    GeneratedMap& mMap;
    bool isFinalPointFound = false;
};

#endif// ASTAR_H
