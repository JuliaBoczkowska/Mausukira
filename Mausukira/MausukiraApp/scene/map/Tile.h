#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "utils/TextureManager.h"

static constexpr unsigned SPRITE_TILE_SIZE = 16;///< Tiles are 16 px wide and 16 px tall
static constexpr int TILE_SIZE = 32;            ///< Tiles are 16 px wide and 16 px tall
static constexpr unsigned SHEET_SIZE = 128u;    ///< One row consists of 8 tiles

using TileID = std::string;

/** Struct containing information about not unique features of tile. */
struct TileModel
{
    TileModel(TextureManager& textureManager, bool isDeadly, TileID name, unsigned id)
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

    sf::Sprite mSprite;
    TextureManager& mTextureManager;

    bool mIsDeadly;
    TileID mName;
    unsigned mID;
};

/** Class that represents unique instance of the tile.
 *  Each instance of a tile has a reference to that shared tile model.
 *  This approach is called flyweight pattern */
class Tile
{
public:
    Tile(TileModel* tileModel, const int& _x, const int& _y)
        : mTileModel(tileModel)
        , x(_x)
        , y(_y)
    {
        mTileModel->mSprite.setPosition(x * (TILE_SIZE), y * (TILE_SIZE));
    }

    Tile() = default;
    ~Tile() = default;

    void draw(sf::RenderWindow& window)
    {
        sf::Sprite& sprite = mTileModel->mSprite;
        sprite.setPosition(x * (TILE_SIZE), y * (TILE_SIZE));
        window.draw(sprite);
    }

    int x;
    int y;
    TileModel* mTileModel;
};

#endif// TILE_H