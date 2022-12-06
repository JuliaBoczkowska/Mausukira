#include "SpriteComponent.h"
#include "TransformComponent.h"

SpriteComponent::SpriteComponent(TransformComponent& transformComponent, sf::Sprite& sprite)
    : mTransformComponent(transformComponent)
    , mCurrentSprite(sprite)
{
    mCurrentSprite.setPosition(mTransformComponent.position());
}

void SpriteComponent::draw(sf::RenderWindow& window)
{
    window.draw(mCurrentSprite);
}

SpriteComponent::SpriteComponent(SpriteComponent&& c) noexcept
    : mTransformComponent(c.mTransformComponent)
{
}

SpriteComponent& SpriteComponent::operator=(SpriteComponent&& other)
{
    mTransformComponent = std::move(other.mTransformComponent);
    return *this;
}

SpriteComponent::SpriteComponent(const SpriteComponent& c)
    : mTransformComponent(c.mTransformComponent)
{
}
void SpriteComponent::moveBy(const sf::Vector2f& mov)
{
    mTransformComponent.moveBy(mov);
    if (mTransformComponent.mPositionOld == mTransformComponent.mPosition)
    {

        mCurrentSprite.move(mov);
    }
}
