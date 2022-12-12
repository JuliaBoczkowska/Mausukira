#ifndef RNDSPRITECOMPONENT_H
#define RNDSPRITECOMPONENT_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "TextureCreator.h"

class RndSpriteComponent
{
public:
    RndSpriteComponent(TextureManager& textureManager);
    void draw(sf::RenderWindow& window);

private:
    TextureCreator mTextCreator;
    std::vector<sf::Sprite> mSpritesParts;
};

#endif// RNDSPRITECOMPONENT_H
