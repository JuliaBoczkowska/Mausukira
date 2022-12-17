#include "RndSpriteComponent.h"

RndSpriteComponent::RndSpriteComponent(EnemyTextureGenerator& enemyTextureCreator)
    : mEnemyTextureCreator(enemyTextureCreator)
{
    mSpritesParts = mEnemyTextureCreator.generate();
    for (auto& sprite: mSpritesParts)
    {
        sprite.setScale(2.f, 2.f);
    }
    mCurrentSprite = mSpritesParts.at(0);
}

RndSpriteComponent::RndSpriteComponent(const RndSpriteComponent& c)
    : mEnemyTextureCreator(c.mEnemyTextureCreator)
    , mSpritesParts(c.mSpritesParts)
{
}

RndSpriteComponent::RndSpriteComponent(RndSpriteComponent&& c) noexcept
    : RndSpriteComponent(c.mEnemyTextureCreator)
{
}

RndSpriteComponent& RndSpriteComponent::operator=(RndSpriteComponent&& other)
{
    mSpritesParts = std::move(other.mSpritesParts);
    mEnemyTextureCreator = std::move(other.mEnemyTextureCreator);
    return *this;
}

void RndSpriteComponent::draw(sf::RenderWindow& window)
{
    for (const auto& sprite: mSpritesParts)
    {
        window.draw(sprite);
    }
}

void RndSpriteComponent::setPosition(const sf::Vector2f& position)
{
    for (auto& sprite: mSpritesParts)
    {
        sprite.setPosition(position);
    }
}

void RndSpriteComponent::moveBy(const sf::Vector2f& mov)
{
    for (auto& sprite: mSpritesParts)
    {
        sprite.move(mov);
    }
}
