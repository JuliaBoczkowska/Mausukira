#ifndef MAPCONTEXT_H
#define MAPCONTEXT_H

#include "Tile.h"
#include <array>
#include <iostream>

#define MAP_SIZE_X 32
#define MAP_SIZE_Y 32
#define MAP_SIZE 1024

struct MapContext
{
    MapContext()
    {
        std::cout << "uwu" << std::endl;
    }
    std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y> mMap{0};
    std::array<std::unique_ptr<Tile>, MAP_SIZE> mTileMap;
    sf::Vector2f centerOfTheFirstRoom{0.f, 0.f};
};


#endif// MAPCONTEXT_H
