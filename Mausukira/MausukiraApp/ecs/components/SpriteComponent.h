#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "TransformComponent.h"

struct SpriteComponent
{
    SpriteComponent(TransformComponent& transformComponent, sf::Sprite& sprite);
    SpriteComponent(const SpriteComponent& c);
    SpriteComponent(SpriteComponent&& c) noexcept;
    SpriteComponent& operator=(SpriteComponent&& other);

    void draw(sf::RenderWindow& window);
    void moveBy(const sf::Vector2f& mov);

    sf::Sprite mCurrentSprite;
    sf::Color mColor{
        1,
        1,
        1,
    };
    unsigned mLayer{0};
    TransformComponent& mTransformComponent;
};
#endif// SPRITECOMPONENT_H
