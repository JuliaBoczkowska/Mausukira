#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(sf::Sprite& sprite)
    : mCurrentSprite(sprite)
{
}

void SpriteComponent::draw(sf::RenderWindow& window)
{
    window.draw(mCurrentSprite);
}


void SpriteComponent::setPosition(const sf::Vector2f& position)
{
    mCurrentSprite.setPosition(position);
}

void SpriteComponent::moveBy(const sf::Vector2f& mov)
{
    mCurrentSprite.move(mov);
}

