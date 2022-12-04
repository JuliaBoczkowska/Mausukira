#ifndef COORDINATESCONVERTER_H
#define COORDINATESCONVERTER_H

#include "SFML/System/Vector2.hpp"
#include "scene/map/Tile/Tile.h"

namespace converter
{
template<typename T>
static sf::Vector2<T> worldCoordinateToTileCoordinate(T worldCoordinateX, T worldCoordinateY)
{
    return sf::Vector2<T>{(worldCoordinateX / Tile::TILE_SIZE),
                          (worldCoordinateY / Tile::TILE_SIZE)};
}

template<typename T>
static sf::Vector2<T> tileToWorldCoordinate(T tileX, T tileY)
{
    return sf::Vector2<T>{(tileX * Tile::TILE_SIZE), (tileY * Tile::TILE_SIZE)};
}

}// namespace converter

#endif// COORDINATESCONVERTER_H
