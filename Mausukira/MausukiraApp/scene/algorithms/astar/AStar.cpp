#include "AStar.h"
#include <algorithm>
#include <stdexcept>
#include "../../map/TerrainGenerator.h"


AStar::AStar(GeneratedMap& map)
    : mMap((map))
    , mMapHeight(mMap.size())
    , mMapWidth(mMap[0].size())
{
}

void AStar::checkTilesAround(const sf::Vector2i& cell, const PathCost& costOfTile)
{
    static const sf::Vector2i neighbouringTiles[] = {
        { 1,  0 },
        { -1, 0 },
        { 0,  1 },
        { 0,  -1 },
    };

    for (int neighbourIndex = 0; neighbourIndex < 4; ++neighbourIndex)
    {

        //TODO CHECK THAT COMMENTED CODE!
        if (const auto closeNode = cell + neighbouringTiles[neighbourIndex]; isInBorders(closeNode))
            // && getCellType(closeNode) != Type::HALL)
        {
            if (closeNode == mFinalPoint)
            {
                isFinalPointFound = true;
                return;
            }

            auto distanceToNeighbouringCell{ 0 };
            switch (mMap[cell.x][cell.y])
            {
                case CellType::ROOM:distanceToNeighbouringCell = 10;
                    break;
                case CellType::NONE:distanceToNeighbouringCell = 5;
                    break;
                case CellType::HALL:distanceToNeighbouringCell = 1;
                    break;
            }

            auto costOfCloseNode = PathCost(costOfTile.mDistanceFromStart
                                            + distanceToNeighbouringCell,
                std::pair<sf::Vector2i, sf::Vector2i>{ closeNode, mFinalPoint }, cell);

            if (auto unvisitedNode = mVisitedTiles.find(closeNode); unvisitedNode == mVisitedTiles.end())
            {
                mUnvisitedTiles.emplace(std::move(costOfCloseNode), closeNode);
            }

        }
    }
}

void AStar::drawFinalPathOnMap(const sf::Vector2i& lastHandledCell)
{
    setCellTypeOnMap(lastHandledCell, CellType::ROOM);
    for (auto tileItCameFrom = mVisitedTiles.at(lastHandledCell).mParentTileCoords;
         tileItCameFrom != mVisitedTiles.at(tileItCameFrom).mParentTileCoords;
         tileItCameFrom = mVisitedTiles.at(tileItCameFrom).mParentTileCoords)
    {
        setCellTypeOnMap(tileItCameFrom, CellType::ROOM);
    }
    setCellTypeOnMap(mStartPoint, CellType::ROOM);
}

void AStar::updateMapAroundTile(const sf::Vector2i& centerOfTileCoordinates, const PathCost& cost)
{
    if (isInBorders(centerOfTileCoordinates))
    {
        checkTilesAround(centerOfTileCoordinates, cost);
        mVisitedTiles.emplace(centerOfTileCoordinates, cost);
    }
    else
    {
        throw std::runtime_error("ERR: AStar::updateMapAroundTile - Out of map border");
    }
}

bool AStar::isInBorders(const sf::Vector2i& tileCoords) const
{
    return tileCoords.x >= 0 && tileCoords.y >= 0 &&
           tileCoords.x < mMapWidth && tileCoords.y < mMapHeight;
}

GeneratedMap AStar::generateHallway(const sf::Vector2i& startingPoint, const sf::Vector2i& finalPoint)
{
    updateMapAroundTile(startingPoint,
        PathCost{ 0, std::pair<sf::Vector2i, sf::Vector2i>{ startingPoint, mFinalPoint }, startingPoint });

    for (auto it = mUnvisitedTiles.begin(); it != mUnvisitedTiles.end(); it = mUnvisitedTiles.begin())
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
    reInitializeAlgorithm(startingPoint, finalPoint);
    return mMap;
}

void AStar::reInitializeAlgorithm(const sf::Vector2i& startingPoint, const sf::Vector2i& finalPoint)
{
    mFinalPoint = finalPoint;
    mStartPoint = startingPoint;
    mUnvisitedTiles.clear();
    mVisitedTiles.clear();
    isFinalPointFound = false;
}

CellType AStar::getCellType(const sf::Vector2i& cell)
{
    return static_cast<CellType>(mMap[cell.x][cell.y]);
}

void AStar::setCellTypeOnMap(const sf::Vector2i& tile, CellType type)
{
    mMap[tile.x][tile.y] = type;
}
