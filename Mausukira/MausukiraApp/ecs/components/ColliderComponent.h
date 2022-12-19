#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H
#include "scene/CollisionBox.h"
#include <SFML/Graphics/Rect.hpp>
#include <string>

struct ColliderComponent
{
    ColliderComponent(const std::string& nameTag, CollisionBox box);
    explicit ColliderComponent(const std::string& nameTag);

    void moveBy(sf::Vector2f position);
    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window);

    CollisionBox mCollisionBox;
    std::string mNameTag;

    bool isCollidingWithBullet{false};
    bool isCollidingWithTile{false};
};
#endif// COLLIDERCOMPONENT_H
