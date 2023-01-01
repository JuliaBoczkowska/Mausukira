#include "SpatialHash.h"
#include "dungeon/map/MapUtils.h"

int SpatialHash::getArrayCoordinates(const ColliderComponent& collider, int i) const
{
    const sf::Transform& matrix = collider.mRectangle.getTransform();
    const auto& [x, y] = matrix.transformPoint(collider.mRectangle.getPoint(i));
    auto [tileX, tileY] = tile_helper::worldCoordinateToTileCoordinate(x, y);
    return tileX + tileY * MAP_SIZE_Y;
}

void SpatialHash::update(ColliderComponent& collider)
{
    for (int i = 0; i < 4; ++i)
    {
        auto key = getArrayCoordinates(collider, i);
        collider.coordOfForEveryCorner[i] = key;
        addCollider(collider, key);
    }
}

void SpatialHash::addCollider(ColliderComponent& collider, int key)
{
    mSpatialHashGrid[key].emplace(&collider);
}

std::set<ColliderComponent*> SpatialHash::getCollidersInTheSameCell(ColliderComponent& collider)
{
    std::set<ColliderComponent*> result;
    for (auto& key: collider.coordOfForEveryCorner)
    {
        auto setOfUniqueColliders = mSpatialHashGrid.find(key);
        if (setOfUniqueColliders != mSpatialHashGrid.end())
        {
            for (auto collider: setOfUniqueColliders->second)
            {
                result.insert(collider);
            }
        }
    }
    return result;
}

void SpatialHash::clearSpatialGridMap()
{
    mSpatialHashGrid.clear();
}
