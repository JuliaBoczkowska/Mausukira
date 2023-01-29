#include "EnemyTextureGenerator.h"
#include "utils/RandomNumberGenerator.h"
#include "utils/SpriteSheetHandler.h"
#include "utils/TextureManager.h"

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

std::pair<std::vector<sf::Sprite>, float> EnemyTextureGenerator::generate()
{
    mCalculatedDefense = 0;
    std::vector<sf::Sprite> spritesPartsToDraw;
    createEnemySpriteElements(spritesPartsToDraw);
    return {spritesPartsToDraw, mCalculatedDefense};
}

void EnemyTextureGenerator::loadEnemyTextures()
{
    mTextureManager.load("ENEMIES", "resources/tiles/enemies.png");
    mTextureSheet = mTextureManager.get("ENEMIES");
}

void EnemyTextureGenerator::createEnemySpriteElements(std::vector<sf::Sprite>& enemySpriteElements)
{
    auto face = generateFace();
    face.setScale({2.f, 2.f});
    enemySpriteElements.emplace_back(face);

    auto helmet = generateHelmet();
    if (helmet)
    {
        enemySpriteElements.push_back(*helmet);
    }

    auto torso = generateTorso();
    if (torso)
    {
        enemySpriteElements.push_back(*torso);
    }

    auto boots = generateBoots();
    if (boots)
    {
        enemySpriteElements.push_back(*boots);
    }
}

std::optional<sf::Sprite> EnemyTextureGenerator::generateBoots()
{
    if (generateIntNumberInRange(1, 4) == 1)
    {
        sf::Sprite sprite = SpriteSheetHandler::extractSpriteFromTileSheet(
            static_cast<int>(EnemySpritesID::BOOTS), mTextureSheet);
        generateArmourType(sprite);
        mCalculatedDefense += mBootsProtection;
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
        mCalculatedDefense += mDiamondDefense;
    }
    else if (percentValue > 10.f && percentValue < 30.f)
    {
        sprite.setColor(GOLD);
        mCalculatedDefense += mGoldDefense;
    }
    else
    {
        sprite.setColor(IRON);
        mCalculatedDefense += mIronDefense;
    }
}

std::optional<sf::Sprite> EnemyTextureGenerator::generateTorso()
{
    if (generateIntNumberInRange(1, 4) == 1)
    {
        sf::Sprite sprite = SpriteSheetHandler::extractSpriteFromTileSheet(
            static_cast<int>(EnemySpritesID::TORSO), mTextureSheet);
        generateArmourType(sprite);
        mCalculatedDefense += mChestplateProtection;
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
        mCalculatedDefense += mHelmetProtection;
        return sprite;
    }
    return std::nullopt;
}

sf::Sprite EnemyTextureGenerator::generateFace()
{
    return SpriteSheetHandler::extractSpriteFromTileSheet(generateIntNumberInRange(0, 6),
                                                          mTextureSheet);
}
EnemyTextureGenerator& EnemyTextureGenerator::operator=(EnemyTextureGenerator&& other)
{
    mTextureManager = std::move(other.mTextureManager);
    return *this;
}
