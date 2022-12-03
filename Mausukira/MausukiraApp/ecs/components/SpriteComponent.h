#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Texture.hpp"

struct SpriteComponent
{
    sf::Color mColor{
        1,
        1,
        1,
    };
    sf::Texture Texture;
    float TilingFactor = 1.0f;

    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent&) = default;
    SpriteComponent(const sf::Color& color)
        : mColor(color)
    {
    }
};

#endif// SPRITECOMPONENT_H
