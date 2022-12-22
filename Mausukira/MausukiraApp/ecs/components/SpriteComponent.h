#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

struct SpriteComponent
{
    SpriteComponent(const sf::Sprite& sprite);

    SpriteComponent(const std::vector<sf::Sprite>& sprites);

    unsigned mScale{ 2 };
    std::vector<sf::Sprite> mSprites;
    sf::Color mColor{ 1, 1, 1 };
    unsigned mLayer{ 0 };
};

#endif// SPRITECOMPONENT_H
