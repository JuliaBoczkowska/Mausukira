#ifndef SPRITESHEETHANDLER_H
#define SPRITESHEETHANDLER_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class SpriteSheetHandler
{
    static constexpr unsigned SPRITE_TILE_SIZE = 16;///< Tiles are 16 px wide and 16 px tall
    static constexpr unsigned SHEET_SIZE = 128u;    ///< One row consists of 8 tiles

public:
    SpriteSheetHandler() = default;

    static sf::Sprite extractTileFromTileSheet(int tilePosition, sf::Sprite& tileSheet);

    static sf::Sprite extractSpriteFromTileSheet(int tilePosition, const sf::Texture& tileSheet);
};

#endif// SPRITESHEETHANDLER_H
