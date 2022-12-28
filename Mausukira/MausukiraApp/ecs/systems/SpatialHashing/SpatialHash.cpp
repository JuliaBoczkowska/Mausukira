#include "SpatialHash.h"
#include "dungeon/map/MapUtils.h"

void SpatialHash::addCollider(ColliderComponent& collider)
{
    for (int i = 0; i < 4; ++i)
    {
        sf::Vector2i key = getKey(collider, i);
        collider.uniqueCellIndex.insert(std::make_pair(key.x, key.y));
        mSpatialHashGrid[key].insert(&collider);
    }
}

sf::Vector2i SpatialHash::getKey(const ColliderComponent& collider, int i) const
{
    auto [x, y] = collider.mRectangle.getPoint(i);
    sf::Vector2f tileCoord = tile_helper::worldCoordinateToTileCoordinate(x, y);
    return sf::Vector2i{ static_cast<int>(tileCoord.x), static_cast<int>(tileCoord.y) };
}

SpatialHash::SpatialHash()
{
}

void SpatialHash::update(ColliderComponent& collider)
{
    removeCollider(collider);
    addCollider(collider);
}

void SpatialHash::removeCollider(ColliderComponent& collider)
{
    for (auto key: collider.uniqueCellIndex)
    {
        mSpatialHashGrid.at(sf::Vector2i{ key.first, key.second }).erase(&collider);
    }
}

std::set<ColliderComponent*> SpatialHash::getCollidersInTheSameCell(ColliderComponent& collider)
{
    std::set<ColliderComponent*> result;
    std::set<std::pair<int, int>> uniqueCellIndex;
    for (int i = 0; i < 4; ++i)
    {
        auto [x, y] = getKey(collider, i);
        std::pair<int, int> pair{ x, y };
        uniqueCellIndex.insert(pair);
    }

    for (auto& elem: uniqueCellIndex)
    {
        auto temp = mSpatialHashGrid.find(sf::Vector2i(elem.first, elem.second));
        result.insert(temp->second.begin(), temp->second.end());
    }
    return result;
}
