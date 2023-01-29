#include "Tile.h"
#include "TileModel.h"
#include "dungeon/map/Constants.h"

Tile::Tile(TileModel* tileModel, const int& x, const int& y)
    : mTileModel(tileModel)
    , mX(x)
    , mY(y)
{
    mSprite = mTileModel->mSprite;
    mSprite.setPosition(mX * (TILE_SIZE), mY * (TILE_SIZE));
    setupCollisionBox();
}

void Tile::setupCollisionBox()
{
    auto rect = mSprite.getGlobalBounds();
    mRectangle.setPosition(rect.left, rect.top);
    mRectangle.setSize(sf::Vector2f(rect.width, rect.height));
    mRectangle.setFillColor(sf::Color::Transparent);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(1);
}

void Tile::draw(sf::RenderWindow& window)
{
    window.draw(mSprite);
    //    if (mColliding)
    //    {
    //        window.draw(mRectangle);
    //    }
}
