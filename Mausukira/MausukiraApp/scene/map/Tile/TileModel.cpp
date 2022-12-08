#include "TileModel.h"

TileModel::TileModel(TextureManager& textureManager, const TileProperties& properties, TileID name,
                     unsigned id)
    : mTextureManager(textureManager)
    , mTileProperties(properties)
    , mName(name)
    , mID(id)
{
    mSprite.setTexture(mTextureManager.get("TILES"));
    sf::IntRect tileBoundaries(mID % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               mID / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               SPRITE_TILE_SIZE, SPRITE_TILE_SIZE);

    mSprite.setTextureRect(tileBoundaries);
    mTextureManager.load(name, std::move(std::make_unique<sf::Texture>(*mSprite.getTexture())));
    mSprite.setScale({2, 2});
}