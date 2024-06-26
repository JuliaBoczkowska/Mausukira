#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "TileModel.h"
#include "utils/TextureManager.h"
#include "dungeon/CollisionBox.h"

/** Class that represents unique instance of the tile.
 *  Each instance of a tile has a reference to that shared tile model.
 *  This approach is called flyweight pattern */
struct Tile
{
    Tile(TileModel* tileModel, const int& x, const int& y);

    ~Tile() = default;

    Tile& operator=(Tile other)
    {
        std::swap(mX, other.mX);
        std::swap(mY, other.mY);
        std::swap(mTileModel, other.mTileModel);
        std::swap(mSprite, other.mSprite);
        std::swap(mRectangle, other.mRectangle);
        std::swap(mColliding, other.mColliding);
    }

    void draw(sf::RenderWindow& window);

    void setupCollisionBox();

    int mX;
    int mY;
    TileModel* mTileModel;
    sf::Sprite mSprite;
    sf::RectangleShape mRectangle;
    bool mColliding{ false };
};

#endif// TILE_H