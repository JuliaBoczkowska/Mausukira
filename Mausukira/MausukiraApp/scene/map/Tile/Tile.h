#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "TileModel.h"
#include "utils/TextureManager.h"


/** Class that represents unique instance of the tile.
 *  Each instance of a tile has a reference to that shared tile model.
 *  This approach is called flyweight pattern */
class Tile
{
public:
    /** Tiles are 16 px wide and 16 px tall */
    static constexpr int TILE_SIZE = 32;
    Tile(TileModel* tileModel, const int& x, const int& y);

    Tile() = default;
    ~Tile() = default;

    void draw(sf::RenderWindow& window);

    int mX;
    int mY;
    TileModel* mTileModel;
    sf::Sprite mSprite;
};
#endif// TILE_H