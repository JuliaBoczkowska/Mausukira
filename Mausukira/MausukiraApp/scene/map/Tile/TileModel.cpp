#include "TileModel.h"
#include "utils/SpriteSheetHandler.h"

TileModel::TileModel(TextureManager& textureManager, const TileProperties& properties, TileID name,
                     unsigned id)
    : mTextureManager(textureManager)
    , mTileProperties(properties)
    , mName(name)
    , mID(id)
{
    mSprite.setTexture(mTextureManager.get("TILES"));


    mTextureManager.load(name, std::move(std::make_unique<sf::Texture>(*SpriteSheetHandler::extractTileFromTileSheet(mID, mSprite).getTexture())));
    mSprite.setScale({2, 2});
}