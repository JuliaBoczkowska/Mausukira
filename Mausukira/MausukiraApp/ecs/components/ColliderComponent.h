#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include "TransformComponent.h"

struct ColliderComponent
{
    void updateCollider(sf::Vector2f newPosition)
    {
    }
    sf::FloatRect collisionBox;
    std::string tag;

    TransformComponent* transform;
};
#endif// COLLIDERCOMPONENT_H
