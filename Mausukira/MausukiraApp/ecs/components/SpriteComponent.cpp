#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const sf::Sprite& sprite)
{
    mSprites.push_back(sprite);
    mSprites[0].setScale(mScale, mScale);

}

SpriteComponent::SpriteComponent(const std::vector<sf::Sprite>& sprites)
{
    mSprites = sprites;
    for (auto& sprite: mSprites)
    {
        sprite.setScale(mScale, mScale);
    }
}