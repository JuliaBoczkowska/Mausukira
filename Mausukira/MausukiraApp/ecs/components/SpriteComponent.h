#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

struct SpriteComponent
{
    SpriteComponent(sf::Sprite& sprite);

    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position);
    void moveBy(const sf::Vector2f& mov);

    sf::Sprite mCurrentSprite;
    sf::Color mColor{1, 1, 1};
    unsigned mLayer{0};
};
#endif// SPRITECOMPONENT_H
