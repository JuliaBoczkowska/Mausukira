#ifndef ENEMYTEXTUREGENERATOR_H
#define ENEMYTEXTUREGENERATOR_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <array>
#include <optional>
#include <vector>

class TextureManager;
class EnemyTextureGenerator
{
#define DIAMOND sf::Color(52, 235, 201)
#define GOLD sf::Color(251, 200, 26)
#define IRON sf::Color(255, 255, 255)

    const float mHelmetProtection = 2;
    const float mBootsProtection = 1;
    const float mChestplateProtection = 4;

    const float mDiamondDefense = 5;
    const float mGoldDefense = 2;
    const float mIronDefense = 1;

public:
    enum class EnemySpritesID
    {
        /** Face is index 0-7 */
        HELMET = 8,
        TORSO = 9,
        BOOTS = 10
    };

    EnemyTextureGenerator(TextureManager& textureManager);
    EnemyTextureGenerator(EnemyTextureGenerator&);
    EnemyTextureGenerator(EnemyTextureGenerator&& c) noexcept;
    EnemyTextureGenerator& operator=(EnemyTextureGenerator&& other);

    void loadEnemyTextures();
    std::pair<std::vector<sf::Sprite>, float> generate();

private:
    void createEnemySpriteElements(std::vector<sf::Sprite>& enemySpriteElements);
    void generateArmourType(sf::Sprite& sprite);
    std::optional<sf::Sprite> generateBoots();
    std::optional<sf::Sprite> generateTorso();
    std::optional<sf::Sprite> generateHelmet();
    sf::Sprite generateFace();

private:
    TextureManager& mTextureManager;
    sf::Texture mTextureSheet;
    float mCalculatedDefense;
};
#endif// ENEMYTEXTUREGENERATOR_H
