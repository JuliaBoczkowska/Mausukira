#ifndef TEXTURECREATOR_H
#define TEXTURECREATOR_H
#include "SFML/Graphics/Sprite.hpp"
#include "TGUI/Texture.hpp"
#include "utils/TextureManager.h"
#include <array>

class TextureCreator
{
public:
    enum class TextureParts
    {
        FACE,
        HEAD,
        TORSO,
        LEGS,
        WEAPON,
    };

    enum class ArmourType
    {
        IRON,
        GOLD,
        DIAMOND
    };

    TextureCreator(TextureManager& textureManager);

    void loadEnemyTextures();
    std::vector<sf::Texture>& generate();

private:
    void createPartialSprite();
    void generateBoots();
    void generateTorso();
    void generateHelmet();

private:
    std::vector<sf::Texture> mTexturePartsToDraw;
    TextureManager& mTextureManager;
};


#endif// TEXTURECREATOR_H
