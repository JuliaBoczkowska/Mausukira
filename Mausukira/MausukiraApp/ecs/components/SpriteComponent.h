#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

struct SpriteComponent
{
    sf::Sprite mCurrentSprite;
    sf::Color mColor{
        1,
        1,
        1,
    };
    unsigned mLayer{0};

    void draw(sf::RenderWindow& window)
    {
        window.draw(mCurrentSprite);
    }
};

#endif// SPRITECOMPONENT_H
