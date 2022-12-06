#include "Tile.h"
#include "TileModel.h"

Tile::Tile(TileModel* tileModel, const int& x, const int& y)
    : mTileModel(tileModel)
    , mX(x)
    , mY(y)
{
    mSprite = mTileModel->mSprite;
    mSprite.setPosition(mX * (TILE_SIZE), mY * (TILE_SIZE));
    mCollisionBox.setup(mSprite.getGlobalBounds());
}

void Tile::draw(sf::RenderWindow& window)
{
    window.draw(mSprite);
    if (mTileModel->mTileProperties.isTraversable == TileModel::TILE_TYPE::NOT_TRAVERSABLE)
    {
        mCollisionBox.draw(window);
    }
}
