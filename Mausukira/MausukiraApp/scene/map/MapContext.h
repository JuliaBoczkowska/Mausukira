#ifndef MAPCONTEXT_H
#define MAPCONTEXT_H

#include "Constants.h"
#include "scene/map/Tile/Tile.h"
#include <array>
#include <iostream>

struct MapContext
{
    std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y> mMap{0};
    std::array<std::unique_ptr<Tile>, MAP_SIZE> mTileMap;
    sf::Vector2f centerOfTheFirstRoom{0.f, 0.f};
};


#endif// MAPCONTEXT_H
