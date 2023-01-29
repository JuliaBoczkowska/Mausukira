#ifndef ASTAR_H
#define ASTAR_H

#include "AStarHelper.h"
#include "dungeon/algorithms/AlgorithmsHelper.h"
#include "dungeon/map/Constants.h"
#include <map>
#include <unordered_map>

enum CellType;
using GeneratedMap = std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y>;

/**
 * @brief Class responsible for A* search.
 */
class AStar
{
public:
    AStar(GeneratedMap& map);

    /**
     * @brief Searches the shortest path from start point to end point.
     * @param startingPoint Start coordinates.
     * @param finalPoint End coordinates.
     * @return Updated map.
     */
    GeneratedMap generateHallway(const sf::Vector2i& startingPoint, const sf::Vector2i& finalPoint);

private:
    /**
     * @brief Checks if the tile is in borders and after checking adds it to closed node list.
     * @param tile Tile's coordinate, on its basis the coordinates of the neighbors are calculated
     * @param cost Current cost of the tile being checked.
     */
    void updateMapAroundTile(const sf::Vector2i& tile, const PathCost& cost);

    /**
     * @brief Checks all 8 neighbours of the tile in order to select one with the best cost
     * function.
     * @param tile Tile's coordinate, on its basis the coordinates of the neighbors are calculated
     * @param costOfTile Current cost of the tile being checked.
     */
    void checkTilesAround(const sf::Vector2i& tile, const PathCost& costOfTile);

    /**
     * @brief Performs backtracking from lat tile to first one.
     * @param lastHandledTile The final destination.
     */
    void drawFinalPathOnMap(const sf::Vector2i& lastHandledTile);

    /**
     * @brief During backtracking the appropriate tiles are assigned on the map.
     * @param tile The coordinates of the tile in the vector.
     * @param type Type of the cell
     */
    void setOnMapTileType(const sf::Vector2i& tile, CellType type);

    /**
     * @brief Reinitialize whole algorithm, so it can be used multiple times
     */
    void reInitializeAlgorithm();

private:
    /** Starting and end coordinates */
    sf::Vector2i mStartPoint;
    sf::Vector2i mFinalPoint;

    /** Visited amd unvisited tiles containers */
    std::map<Vertex, PathCost> mVisitedTiles;
    std::multimap<PathCost, sf::Vector2i> mUnvisitedTiles;

    /** Output of the algorithm */
    GeneratedMap& mMap;
    bool isFinalPointFound = false;
};

#endif// ASTAR_H
