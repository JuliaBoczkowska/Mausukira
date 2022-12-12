#include "RndSpriteComponent.h"

RndSpriteComponent::RndSpriteComponent(TextureManager& textureManager)
    : mTextCreator(textureManager)
{
    for (auto texturePart: mTextCreator.generate())
    {
        mSpritesParts.push_back(sf::Sprite(texturePart));
    }
}
void RndSpriteComponent::draw(sf::RenderWindow& window)
{
    for (auto texturePart: mSpritesParts)
    {
        sf::Sprite sprite(texturePart);
        window.draw(texturePart);
    }
}
