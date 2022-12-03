#ifndef COORDINATESCONVERTER_H
#define COORDINATESCONVERTER_H

#include "../map/Tile.h"
#include "SFML/System/Vector2.hpp"

namespace converter
{
template<typename T>
static sf::Vector2<T> worldCoordinateToTileCoordinate(T worldCoordinateX, T worldCoordinateY)
{
    return sf::Vector2<T>{(worldCoordinateX / TILE_SIZE), (worldCoordinateY / TILE_SIZE)};
}

template<typename T>
static sf::Vector2<T> tileToWorldCoordinate(T tileX, T tileY)
{
    return sf::Vector2<T>{(tileX * TILE_SIZE), (tileY * TILE_SIZE)};
}

}// namespace converter

#endif// COORDINATESCONVERTER_H
