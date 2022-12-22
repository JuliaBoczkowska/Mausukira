#ifndef ENEMYTEXTUREGENERATOR_H
#define ENEMYTEXTUREGENERATOR_H
#include "SFML/Graphics/Sprite.hpp"
#include "TGUI/Texture.hpp"
#include "utils/TextureManager.h"
#include <array>
#include <xtr1common>

class EnemyTextureGenerator
{
#define DIAMOND sf::Color(52, 235, 201)
#define GOLD sf::Color(251, 200, 26)
#define IRON sf::Color(255, 255, 255)

public:
    enum class EnemySpritesID
    {
        /** Face is present until 7 */
        HELMET = 8,
        TORSO = 9,
        BOOTS = 10
    };

    EnemyTextureGenerator(TextureManager& textureManager);
    EnemyTextureGenerator(EnemyTextureGenerator&);
    EnemyTextureGenerator(EnemyTextureGenerator&& c) noexcept;
    EnemyTextureGenerator& operator=(EnemyTextureGenerator&& other)
    {
        mTextureManager = std::move(other.mTextureManager);
        return *this;
    }

    void loadEnemyTextures();
    std::vector<sf::Sprite> generate();

private:
    void createPartialSprite(std::vector<sf::Sprite>& spritesPartsToDraw);
    void generateArmourType(sf::Sprite& sprite);
    std::optional<sf::Sprite> generateBoots();
    std::optional<sf::Sprite> generateTorso();
    std::optional<sf::Sprite> generateHelmet();
    std::optional<sf::Sprite> generateFace();

private:
    TextureManager& mTextureManager;
    sf::Texture mTextureSheet;
};


#endif// ENEMYTEXTUREGENERATOR_H
