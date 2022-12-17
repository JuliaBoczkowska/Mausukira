#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(const std::string& nameTag, CollisionBox box)
    : mNameTag(nameTag)
    , mCollisionBox(box)
{
}

ColliderComponent::ColliderComponent(const std::string& nameTag)
{
}

void ColliderComponent::moveBy(sf::Vector2f position)
{
    mCollisionBox.moveCollisionBox(position);
}

void ColliderComponent::setPosition(sf::Vector2f position)
{
    mCollisionBox.setPosition(position);
}

void ColliderComponent::draw(sf::RenderWindow& window)
{
    mCollisionBox.draw(window);
}
