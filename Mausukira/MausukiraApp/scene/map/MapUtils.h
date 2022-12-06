#ifndef MAPUTILS_H
#define MAPUTILS_H
#include "MapContext.h"
#include "scene/CollisionBox.h"
#include "scene/map/Tile/Tile.h"
#include "scene/map/Tile/TileHelper.h"
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

static std::vector<CollisionBox*> getSurroundingCollisionBoxes(sf::Vector2f playerPosition,
                                                               TileMap& mTileMap)
{
    sf::Vector2i playerTileCoordinates = static_cast<sf::Vector2i>(
        tile_helper::worldCoordinateToTileCoordinate(playerPosition.x, playerPosition.y));

    std::vector<CollisionBox*> collisions;
//    for (int neighbourIndex = 0; neighbourIndex < 8; ++neighbourIndex)
//    {
//        if (const auto neighbouringTile =
//                playerTileCoordinates + tile_helper::neighbouringEightTiles[neighbourIndex];
//            tile_helper::isInBorders(neighbouringTile))
//        {
    for (int x = 0; x < MAP_SIZE_X; ++x)
    {
        for (int y = 0; y < MAP_SIZE_Y; ++y)
        {
            auto& tile = getTile(mTileMap, x, y);
            if (tile.mTileModel->mTileProperties.isTraversable ==
                TileModel::TILE_TYPE::NOT_TRAVERSABLE)
            {
                collisions.push_back(&tile.mCollisionBox);
            }
        }
    }

       // }
    //}
    return collisions;
}
}// namespace map_utils
#endif// MAPUTILS_H
