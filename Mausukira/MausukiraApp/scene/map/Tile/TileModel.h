#ifndef TILEMODEL_H
#define TILEMODEL_H
#include "SFML/Graphics/Sprite.hpp"
#include <string>
#include <utils/TextureManager.h>

using TileID = std::string;

/** Struct containing information about not unique features of tile. */
struct TileModel
{
    static constexpr unsigned SPRITE_TILE_SIZE = 16;///< Tiles are 16 px wide and 16 px tall
    static constexpr unsigned SHEET_SIZE = 128u;    ///< One row consists of 8 tiles

    enum class IS_DEADLY
    {
        NOT_DEADLY,
        DEADLY
    };

    TileModel(TextureManager& textureManager, bool isDeadly, TileID name, unsigned id);

    sf::Sprite mSprite;
    TextureManager& mTextureManager;

    bool mIsDeadly;
    TileID mName;
    unsigned mID;
};

#endif// TILEMODEL_H
