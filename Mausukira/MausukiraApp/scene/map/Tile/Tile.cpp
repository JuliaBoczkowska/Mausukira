#include "Tile.h"
#include "TileModel.h"

Tile::Tile(TileModel* tileModel, const int& x, const int& y)
    : mTileModel(tileModel)
    , mX(x)
    , mY(y)
{
    mTileModel->mSprite.setPosition(mX * (TILE_SIZE), mY * (TILE_SIZE));
}

void Tile::draw(sf::RenderWindow& window)
{
    sf::Sprite& sprite = mTileModel->mSprite;
    sprite.setPosition(mX * (TILE_SIZE), mY * (TILE_SIZE));
    window.draw(sprite);
}
