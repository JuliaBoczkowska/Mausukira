#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics/Sprite.hpp"
#include "../../states_stack/SharedContext.h"

static constexpr unsigned TILE_SIZE = 16u;           ///< Tiles are going to be 32 px wide and 32 px tall
static constexpr unsigned SHEET_SIZE = 128u;          ///< One row consists of 32 tiles

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
            mID % (SHEET_SIZE / TILE_SIZE) * TILE_SIZE,
            mID / (SHEET_SIZE / TILE_SIZE) * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE);

        mSprite.setTextureRect(tileBoundaries);
        mSprite.setScale({ mScaleFactor, mScaleFactor });
    }

    sf::Sprite mSprite;
    SharedContext& mCtx;
    const float mScaleFactor{ 2.f };

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