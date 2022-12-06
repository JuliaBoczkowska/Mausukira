#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H
#include "scene/CollisionBox.h"
#include <SFML/Graphics/Rect.hpp>
#include <string>

struct ColliderComponent
{
    ColliderComponent(const std::string& nameTag, CollisionBox box);
    //    ColliderComponent(const ColliderComponent& c);
    //    ColliderComponent(ColliderComponent&& c) noexcept;
    //    ColliderComponent& operator=(ColliderComponent&& other);

    void moveBy(sf::Vector2f position);
    void draw(sf::RenderWindow& window);

    CollisionBox mCollisionBox;
    std::string mNameTag;
    bool mIsColliding = false;
};
#endif// COLLIDERCOMPONENT_H
