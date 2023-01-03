#ifndef MAPCONTEXT_H
#define MAPCONTEXT_H

#include "Constants.h"
#include "dungeon/map/room/Room.h"
#include "dungeon/map/Tile/Tile.h"
#include <array>
#include <iostream>

struct MapContext
{
    MapContext()
    {

    }

    std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y> mMap{ 0 };
    std::array<std::unique_ptr<Tile>, MAP_SIZE> mTileMap;
    sf::Vector2i mCenterOfTheFirstRoom{ 0, 0 };
    std::list<Room> mRooms{};
};

#endif// MAPCONTEXT_H
