#include "TileModel.h"

TileModel::TileModel(TextureManager& textureManager, bool isDeadly, TileID name, unsigned id)
    : mTextureManager(textureManager)
    , mIsDeadly(isDeadly)
    , mName(name)
    , mID(id)
{
    mSprite.setTexture(mTextureManager.get("TILES"));

    sf::IntRect tileBoundaries(mID % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               mID / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               SPRITE_TILE_SIZE, SPRITE_TILE_SIZE);

    mSprite.setTextureRect(tileBoundaries);
    mSprite.setScale({2, 2});
}