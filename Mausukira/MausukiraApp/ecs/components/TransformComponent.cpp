#include "TransformComponent.h"

const sf::Vector2f& TransformComponent::operator()()
{
    return mPosition;
}

const sf::Vector2f& TransformComponent::operator()() const
{
    return mPosition;
}

TransformComponent::TransformComponent(ColliderComponent& colliderComponent, sf::Vector2f position)
    : mColliderComponent(colliderComponent)
    , mPosition(position)
{
    mColliderComponent.mCollisionBox.setInitialPosition(position);
}

TransformComponent::TransformComponent(const TransformComponent& c)
    : mColliderComponent(c.mColliderComponent)
    , mPosition(c.mPosition)
{
}

TransformComponent::TransformComponent(TransformComponent&& c) noexcept
    : TransformComponent(c.mColliderComponent, c.mPosition)
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
    mPositionOld = mPosition;
    mPosition = position;
    mColliderComponent.mCollisionBox.setInitialPosition(mPosition);
}

void TransformComponent::moveBy(const sf::Vector2f& mov)
{
    mPositionOld = mPosition;
    mPosition += mov;
    mColliderComponent.moveBy(mov);
}

sf::Vector2f TransformComponent::position()
{
    return mPosition;
}