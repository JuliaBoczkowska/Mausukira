#ifndef MAPUTILS_H
#define MAPUTILS_H

#include "MapContext.h"
#include "dungeon/map/Tile/TileHelper.h"
#include <array>

namespace map_utils
{
    using TileMap = std::array<std::unique_ptr<Tile>, MAP_SIZE>;

    static unsigned int convertCoordsTo1D(const unsigned int& x, const unsigned int& y)
    {
        return (x * MAP_SIZE_X) + y;
    }

    static Tile& getTile(TileMap& mTileMap, const unsigned int& x, const unsigned int& y)
    {
        auto tile = mTileMap.at(map_utils::convertCoordsTo1D(x, y)).get();
        return *tile;
    }

    static std::vector<sf::RectangleShape*> getSurroundingTileCollisionBoxes(sf::Vector2f futurePosition,
        TileMap& mTileMap)
    {
        sf::Vector2i playerTileCoordinates = static_cast<sf::Vector2i>(
            tile_helper::worldCoordinateToTileCoordinate(futurePosition.x, futurePosition.y));

        std::vector<sf::RectangleShape*> collisions;
        for (int neighbourIndex = 0; neighbourIndex < 8; ++neighbourIndex)
        {
            const auto neighbouringTile = playerTileCoordinates + tile_helper::neighbouringEightTiles[neighbourIndex];
            if (tile_helper::isInBorders(neighbouringTile))
            {
                auto& tile = getTile(mTileMap, neighbouringTile.x, neighbouringTile.y);
                if (tile.mTileModel->mTileProperties.isTraversable ==
                    TileModel::TILE_TYPE::NOT_TRAVERSABLE)
                {
                    tile.mColliding = true;
                    collisions.push_back(&tile.mRectangle);
                }
            }
        }
        return collisions;
    }

//    static std::vector<ColliderComponent*> getSurroundingCollisionBoxes(sf::Vector2f position,
//        TileMap& mTileMap)
//    {
//        sf::Vector2i objectTileCoordinates = static_cast<sf::Vector2i>(
//            tile_helper::worldCoordinateToTileCoordinate(position.x, position.y));
//
//        std::vector<ColliderComponent*> collisions;
//
//        for (int neighbourIndex = 0; neighbourIndex < 8; ++neighbourIndex)
//        {
//            const auto neighbouringTile = objectTileCoordinates + tile_helper::neighbouringEightTiles[neighbourIndex];
//            if (tile_helper::isInBorders(neighbouringTile))
//            {
//
//                auto view = mRegistry.view<AttachmentPoint, ColliderComponent, ProjectileCollider>();
//                for (auto entity: view)
//                {
//                    auto [attachmentPoint, colliderC, projectile] = view.get(entity);
//                    auto parent = attachmentPoint.parent;
//
//                    auto& position = mRegistry.get<PositionComponent>(parent).mPosition;
//            }
//        }
//        return collisions;
//    }
}// namespace map_utils
#endif// MAPUTILS_H
