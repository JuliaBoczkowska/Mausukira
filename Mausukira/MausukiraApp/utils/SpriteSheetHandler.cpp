#include "SpriteSheetHandler.h"
#include "SFML/Graphics/Sprite.hpp"

sf::Sprite SpriteSheetHandler::extractTileFromTileSheet(int tilePosition, sf::Sprite& tileSheet)
{
    sf::IntRect tileBoundaries(tilePosition % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
        tilePosition / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
        SPRITE_TILE_SIZE, SPRITE_TILE_SIZE);
    tileSheet.setTextureRect(tileBoundaries);

    return tileSheet;
}

sf::Sprite SpriteSheetHandler::extractSpriteFromTileSheet(int tilePosition, const sf::Texture& tileSheet)
{
    sf::Sprite sprite(tileSheet);
    sf::IntRect tileBoundaries(tilePosition % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
        tilePosition / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
        SPRITE_TILE_SIZE, SPRITE_TILE_SIZE);
    sprite.setTextureRect(tileBoundaries);

    return sprite;
}
