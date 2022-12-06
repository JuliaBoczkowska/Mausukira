#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(const std::string& nameTag, CollisionBox box)
    : mNameTag(nameTag)
{
    mCollisionBox = box;
}

void ColliderComponent::moveBy(sf::Vector2f position)
{
    mCollisionBox.updatePosition(position);
}

void ColliderComponent::draw(sf::RenderWindow& window)
{
    mCollisionBox.draw(window);
}
