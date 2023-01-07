#include "AStar.h"
#include "dungeon/DungeonGenerator.h"
#include "dungeon/map/Tile/TileHelper.h"
#include <algorithm>
#include <stdexcept>

AStar::AStar(GeneratedMap& map)
    : mMap((map))
{
}

void AStar::checkTilesAround(const sf::Vector2i& tile, const PathCost& costOfTile)
{
    for (int neighbourIndex = 0; neighbourIndex < 4; ++neighbourIndex)
    {
        if (const auto closeNode = tile + tile_helper::neighbouringFourTiles[neighbourIndex];
            tile_helper::isInBorders(closeNode))
        {
            if (closeNode == mFinalPoint)
            {
                isFinalPointFound = true;
                return;
            }

            auto distanceToNeighbouringCell{0};
            switch (mMap[tile.x][tile.y])
            {
                case CellType::ROOM: distanceToNeighbouringCell = 10; break;
                case CellType::NONE: distanceToNeighbouringCell = 5; break;
                case CellType::HALL: distanceToNeighbouringCell = 1; break;
            }

            auto costOfCloseNode =
                PathCost(costOfTile.mDistanceFromStart + distanceToNeighbouringCell,
                         std::pair<sf::Vector2i, sf::Vector2i>{closeNode, mFinalPoint}, tile);

            if (auto unvisitedNode = mVisitedTiles.find(closeNode);
                unvisitedNode == mVisitedTiles.end())
            {
                mUnvisitedTiles.emplace(std::move(costOfCloseNode), closeNode);
            }
        }
    }
}

void AStar::drawFinalPathOnMap(const sf::Vector2i& lastHandledTile)
{
    setOnMapTileType(lastHandledTile, CellType::ROOM);
    for (auto tileItCameFrom = mVisitedTiles.at(lastHandledTile).mParentTileCoords,
              lastTile = lastHandledTile;
         tileItCameFrom != mVisitedTiles.at(tileItCameFrom).mParentTileCoords;
         lastTile = tileItCameFrom,
              tileItCameFrom = mVisitedTiles.at(tileItCameFrom).mParentTileCoords)
    {
        auto lastIdx = lastTile - tileItCameFrom;
        if (lastIdx.x == -1 || lastIdx.x == 1)
        {
            setOnMapTileType(sf::Vector2i{tileItCameFrom.x, tileItCameFrom.y + 1}, CellType::ROOM);
        }
        if (lastIdx.y == -1 || lastIdx.y == 1)
        {
            setOnMapTileType(sf::Vector2i{tileItCameFrom.x + 1, tileItCameFrom.y}, CellType::ROOM);
        }
        setOnMapTileType(tileItCameFrom, CellType::ROOM);
    }
    setOnMapTileType(mStartPoint, CellType::ROOM);
}

void AStar::updateMapAroundTile(const sf::Vector2i& centerOfTileCoordinates, const PathCost& cost)
{
    if (tile_helper::isInBorders(centerOfTileCoordinates))
    {
        checkTilesAround(centerOfTileCoordinates, cost);
        mVisitedTiles.emplace(centerOfTileCoordinates, cost);
    }
    else
    {
        throw std::runtime_error("ERR: AStar::updateMapAroundTile - Out of map border");
    }
}

GeneratedMap AStar::generateHallway(const sf::Vector2i& startingPoint,
                                    const sf::Vector2i& finalPoint)
{
    mFinalPoint = finalPoint;
    mStartPoint = startingPoint;
    updateMapAroundTile(startingPoint,
                        PathCost{0,
                                 std::pair<sf::Vector2i, sf::Vector2i>{startingPoint, mFinalPoint},
                                 startingPoint});

    for (auto it = mUnvisitedTiles.begin(); it != mUnvisitedTiles.end();
         it = mUnvisitedTiles.begin())
    {
        const auto& [cost, tile] = *it;

        if (mVisitedTiles.find(tile) != mVisitedTiles.end())
        {
            mUnvisitedTiles.erase(it);
            continue;
        }
        updateMapAroundTile(tile, cost);

        if (isFinalPointFound)
        {
            drawFinalPathOnMap(tile);
            break;
        }

        mUnvisitedTiles.erase(it);
    }
    reInitializeAlgorithm();
    return mMap;
}

void AStar::reInitializeAlgorithm()
{
    mUnvisitedTiles.clear();
    mVisitedTiles.clear();
    isFinalPointFound = false;
}

void AStar::setOnMapTileType(const sf::Vector2i& tile, CellType type)
{
    mMap[tile.x][tile.y] = type;
}
