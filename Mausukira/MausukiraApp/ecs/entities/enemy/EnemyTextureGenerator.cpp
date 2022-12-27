#include "EnemyTextureGenerator.h"
#include "utils/RandomNumberGenerator.h"
#include "utils/SpriteSheetHandler.h"

EnemyTextureGenerator::EnemyTextureGenerator(TextureManager& textureManager)
    : mTextureManager(textureManager)
{
    loadEnemyTextures();
}

EnemyTextureGenerator::EnemyTextureGenerator(EnemyTextureGenerator& c)
    : mTextureManager(c.mTextureManager)
{
}


EnemyTextureGenerator::EnemyTextureGenerator(EnemyTextureGenerator&& c) noexcept
    : EnemyTextureGenerator(c.mTextureManager)
{
}

std::vector<sf::Sprite> EnemyTextureGenerator::generate()
{
    std::vector<sf::Sprite> spritesPartsToDraw;
    createPartialSprite(spritesPartsToDraw);
    return spritesPartsToDraw;
}

void EnemyTextureGenerator::loadEnemyTextures()
{
    mTextureManager.load("ENEMIES", "resources/tiles/enemies.png");
    mTextureSheet = mTextureManager.get("ENEMIES");
}

void EnemyTextureGenerator::createPartialSprite(std::vector<sf::Sprite>& spritesPartsToDraw)
{
    /** 20% chance to generate any of the armour type 1:4 chances*/
    auto face = generateFace();
    if (face)
    {
        face->setScale({ 2.f, 2.f });
        spritesPartsToDraw.emplace_back(*face);
    }
    auto helmet = generateHelmet();
    if (helmet)
    {
        spritesPartsToDraw.push_back(*helmet);
    }

    auto torso = generateTorso();
    if (torso)
    {
        spritesPartsToDraw.push_back(*torso);
    }

    auto boots = generateBoots();
    if (boots)
    {
        spritesPartsToDraw.push_back(*boots);
    }
}

std::optional<sf::Sprite> EnemyTextureGenerator::generateBoots()
{
    if (generateIntNumberInRange(1, 4) == 1)
    {
        sf::Sprite sprite = SpriteSheetHandler::extractSpriteFromTileSheet(
            static_cast<int>(EnemySpritesID::BOOTS), mTextureSheet);
        generateArmourType(sprite);
        return sprite;
    }
    return std::nullopt;
}

void EnemyTextureGenerator::generateArmourType(sf::Sprite& sprite)
{
    auto percentValue = generateFloatNumberInRange(0.f, 1.f) * 100;

    if (percentValue <= 10.f)
    {
        sprite.setColor(DIAMOND);
    }
    else if (percentValue > 10.f && percentValue < 30.f)
    {
        sprite.setColor(GOLD);
    }
    else
    {
        sprite.setColor(IRON);
    }
}

std::optional<sf::Sprite> EnemyTextureGenerator::generateTorso()
{
    if (generateIntNumberInRange(1, 4) == 1)
    {
        sf::Sprite sprite = SpriteSheetHandler::extractSpriteFromTileSheet(
            static_cast<int>(EnemySpritesID::TORSO), mTextureSheet);
        generateArmourType(sprite);
        return sprite;
    }
    return std::nullopt;
}

std::optional<sf::Sprite> EnemyTextureGenerator::generateHelmet()
{
    if (generateIntNumberInRange(1, 4) == 1)
    {
        sf::Sprite sprite = SpriteSheetHandler::extractSpriteFromTileSheet(
            static_cast<int>(EnemySpritesID::HELMET), mTextureSheet);
        generateArmourType(sprite);
        return sprite;
    }
    return std::nullopt;
}

std::optional<sf::Sprite> EnemyTextureGenerator::generateFace()
{
    return SpriteSheetHandler::extractSpriteFromTileSheet(generateIntNumberInRange(0, 6),
        mTextureSheet);
}
