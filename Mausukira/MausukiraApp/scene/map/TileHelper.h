#ifndef TILEHELPER_H
#define TILEHELPER_H

#include "SFML/System/Vector2.hpp"

namespace tile_helper
{
// clang-format off
    static const sf::Vector2i neighbouringEightTiles[8] = {
        {-1,  1}, {0,  1}, {1,  1},
        {-1,  0},          {1,  0},
        {-1, -1}, {0, -1}, {1, -1}
    };

    static const sf::Vector2i neighbouringFourTiles[4] = {
    {0,  -1},{-1, 0},
    {1, 0},{0, 1},
    };

    static const sf::Vector2i cornerTiles[4] = {
    {-1, -1} , {1, -1}, {-1, 1}, {1, 1}
    };
// clang-format on

static bool isInBorders(const sf::Vector2i& tileCoords)
{
    return tileCoords.x >= 0 && tileCoords.y >= 0 && tileCoords.x < 32 && tileCoords.y < 32;
}
}// namespace tile_helper


#endif// TILEHELPER_H
