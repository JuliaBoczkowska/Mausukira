#ifndef ASTARHELPER_H
#define ASTARHELPER_H

#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <utility>

/**
 * @brief Every tile used in A* algorithm, has some distance from the start, to the end and
 *        overall path cost.
 */
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

    /** Hashing function for unordered map */
    template<class T1, class T2>
    std::size_t operator()(std::pair<T1, T2> const& v) const
    {
        return std::hash<T1>()(v.size());
    }

    /** Comparison operator. */
    bool operator<(const PathCost& rhs) const
    {
        return mOverallCost < rhs.mOverallCost;
    }

    /**
     * @brief Euclidean distance distance function for A* algorithm.
     * @param tiles to measure distance between.
     * @return Calculated distance.
     */
    float calculateDistance(std::pair<sf::Vector2i, sf::Vector2i> tiles)
    {
        auto [firstTile, secondTile] = tiles;
        auto distanceX = firstTile.x - secondTile.x;
        auto distanceY = firstTile.y - secondTile.y;
        return std::sqrt(distanceX * distanceX + distanceY * distanceY) * 10;
    }

    int mDistanceFromStart;
    int mDistanceToEnd;
    sf::Vector2i mParentTileCoords;
    int mOverallCost;
};

#endif// ASTARHELPER_H
