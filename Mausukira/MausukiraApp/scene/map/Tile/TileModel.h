#ifndef TILEMODEL_H
#define TILEMODEL_H
#include "SFML/Graphics/Sprite.hpp"
#include <string>
#include <utils/TextureManager.h>

using TileID = std::string;

/** Struct containing information about not unique features of tile. */
struct TileModel
{
    enum class TILE_TYPE
    {
        NOT_TRAVERSABLE = 0,
        TRAVERSABLE = 1
    };

    enum class DANGEROUS
    {
        NOT_DEADLY,
        DEADLY
    };

    struct TileProperties
    {
        DANGEROUS mIsDeadly;
        TILE_TYPE isTraversable;
    };

    static constexpr unsigned SPRITE_TILE_SIZE = 16;///< Tiles are 16 px wide and 16 px tall
    static constexpr unsigned SHEET_SIZE = 128u;    ///< One row consists of 8 tiles
    TileModel(TextureManager& textureManager, const TileProperties& properties, TileID name,
              unsigned id);

    sf::Sprite mSprite;
    TextureManager& mTextureManager;
    TileProperties mTileProperties;

    TileID mName;
    unsigned mID;
};

#endif// TILEMODEL_H
