#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics/Sprite.hpp"
#include "../../states_stack/SharedContext.h"

static constexpr unsigned SPRITE_TILE_SIZE = 16;       ///< Tiles are 16 px wide and 16 px tall
static constexpr int TILE_SIZE = 32;                   ///< Tiles are 16 px wide and 16 px tall
static constexpr unsigned SHEET_SIZE = 128u;           ///< One row consists of 8 tiles

enum TileID
{
    FLOOR = 0,
    WALL,
    LAVA
};

/** Struct containing information about not unique features of tile. */
struct TileModel
{
    TileModel(SharedContext& mSharedCtx, bool isDeadly, TileID id)
        : mCtx(mSharedCtx)
        , mIsDeadly(isDeadly)
        , mID(id)
    {
        TextureManager* textureManager = mCtx.textureManager;
        mSprite.setTexture(textureManager->get("TILE"));

        sf::IntRect tileBoundaries(
            mID % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
            mID / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
            SPRITE_TILE_SIZE,
            SPRITE_TILE_SIZE);

        mSprite.setTextureRect(tileBoundaries);
        mSprite.setScale({ 2, 2 });
    }

    sf::Sprite mSprite;
    SharedContext& mCtx;

    bool mIsDeadly;
    TileID mID;
};

/** Class that represents unique instance of the tile.
 *  Each instance of a tile has a reference to that shared tile model.
 *  This approach is called flyweight pattern */
class Tile
{
public:
    Tile(TileModel* tileModel)
        : mTileModel(tileModel)
    {
    }

    Tile() = default;

    ~Tile() = default;

    TileModel* mTileModel;
};

#endif //TILE_H