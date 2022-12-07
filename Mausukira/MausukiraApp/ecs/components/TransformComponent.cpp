#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"

const sf::Vector2f& TransformComponent::operator()()
{
    return mPosition;
}

const sf::Vector2f& TransformComponent::operator()() const
{
    return mPosition;
}

TransformComponent::TransformComponent(ColliderComponent& colliderComponent,
                                       SpriteComponent& spriteComponent, sf::Vector2f position)
    : mColliderComponent(colliderComponent)
    , mSpriteComponent(spriteComponent)
    , mPosition(position)
{
    mColliderComponent.setPosition(position);
    mSpriteComponent.setPosition(position);
}

TransformComponent::TransformComponent(const TransformComponent& c)
    : mColliderComponent(c.mColliderComponent)
    , mSpriteComponent(c.mSpriteComponent)
    , mPosition(c.mPosition)
{
}

TransformComponent::TransformComponent(TransformComponent&& c) noexcept
    : TransformComponent(c.mColliderComponent, c.mSpriteComponent, c.mPosition)
{
}

TransformComponent& TransformComponent::operator=(TransformComponent&& other)
{
    mColliderComponent = std::move(other.mColliderComponent);
    mPosition = std::move(other.mPosition);
    return *this;
}

void TransformComponent::setPosition(sf::Vector2f position)
{
    mPosition = position;
    mColliderComponent.setPosition(position);
    mSpriteComponent.setPosition(position);
}

void TransformComponent::moveBy(const sf::Vector2f& mov)
{
    mPosition += mov;
    mColliderComponent.moveBy(mov);
    mSpriteComponent.moveBy(mov);
}