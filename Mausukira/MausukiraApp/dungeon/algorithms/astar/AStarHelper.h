#ifndef ASTARHELPER_H
#define ASTARHELPER_H

#include "../Coordinate.h"
#include "SFML/System/Vector2.hpp"
#include <array>
#include <vector>

struct PathCost
{
public:
    PathCost(int distanceFromStart, std::pair<sf::Vector2i, sf::Vector2i> cells,
             sf::Vector2i cameFrom)
        : mDistanceFromStart(distanceFromStart)
        , mParentTileCoords(std::move(cameFrom))
    {
        mDistanceToEnd = calculateDistance(cells);
        mOverallCost = distanceFromStart + mDistanceToEnd;
    }

    PathCost(const PathCost&) = default;
    PathCost(PathCost&&) = default;

    template<class T1, class T2>
    std::size_t operator()(std::pair<T1, T2> const& v) const
    {
        return std::hash<T1>()(v.size());
    }

    bool operator<(const PathCost& rhs) const
    {
        return mOverallCost < rhs.mOverallCost;
    }

    float calculateDistance(std::pair<sf::Vector2i, sf::Vector2i> cells)
    {
        auto [firstCell, secondCell] = cells;
        auto distanceX = firstCell.x - secondCell.x;
        auto distanceY = firstCell.y - secondCell.y;
        return std::sqrt(distanceX * distanceX + distanceY * distanceY) * 10;
    }

    int mDistanceFromStart;
    int mDistanceToEnd;
    sf::Vector2i mParentTileCoords;
    int mOverallCost;
};

#endif// ASTARHELPER_H
