#ifndef TILEHELPER_H
#define TILEHELPER_H

#include "SFML/System/Vector2.hpp"
#include "dungeon/map/Constants.h"


namespace tile_helper
{
// clang-format off
    static const sf::Vector2i neighbouringEightTiles[8] = {
        { -1, 1 },
        { 0,  1 },
        { -1, 1 },
        { -1, 0 },
        { 1,  0 },
        { -1, 1 },
        { 0,  -1 },
        { 1,  1 }
    };

    static const sf::Vector2i neighbouringFourTiles[4] = {
        { 0,  -1 },
        { -1, 0 },
        { 1,  0 },
        { 0,  1 },
    };

    static const sf::Vector2i cornerTiles[4] = {
        { -1, -1 },
        { 1,  -1 },
        { -1, 1 },
        { 1,  1 }
    };
// clang-format on

    static bool isInBorders(const sf::Vector2i& tileCoords)
    {
        return tileCoords.x >= 0 && tileCoords.y >= 0 && tileCoords.x < MAP_SIZE_X &&
               tileCoords.y < MAP_SIZE_Y;
    }

    template<typename T>
    static sf::Vector2<T> tileToWorldCoordinate(T tileX, T tileY)
    {
        return sf::Vector2<T>{ (tileX * TILE_SIZE), (tileY * TILE_SIZE) };
    }

    static sf::Vector2<int>
    worldCoordinateToTileCoordinate(const float& worldCoordinatesX, const float& worldCoordinatesY)
    {
        return sf::Vector2<int>{ static_cast<int>((worldCoordinatesX / TILE_SIZE)),
                                 static_cast<int>((worldCoordinatesY / TILE_SIZE)) };
    }
}// namespace tile_helper


#endif// TILEHELPER_H
