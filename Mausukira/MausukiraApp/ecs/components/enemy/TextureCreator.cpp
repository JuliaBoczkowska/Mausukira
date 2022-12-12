#include "TextureCreator.h"
#include "utils/RandomNumberGenerator.h"
#include <fstream>
#include <json/json.h>

TextureCreator::TextureCreator(TextureManager& textureManager)
    : mTextureManager(textureManager)
{
    loadEnemyTextures();
}

std::vector<sf::Texture>& TextureCreator::generate()
{
    return mTexturePartsToDraw;
}

void TextureCreator::loadEnemyTextures()
{
    mTextureManager.load("ENEMIES", "resources/tiles/enemies.png");
    sf::Texture txt = mTextureManager.get("ENEMIES");
}

void TextureCreator::createPartialSprite()
{
    /** 20% chance to generate any of the armour type */
    generateHelmet();
    generateTorso();
    generateBoots();
}

void TextureCreator::generateBoots()
{
}

void TextureCreator::generateTorso()
{
}

void TextureCreator::generateHelmet()
{
    //    if(generateIntNumberInRange(1, 5))
    //    {
    //        mTexturePartsToDraw.push_back()
    //    }
}
