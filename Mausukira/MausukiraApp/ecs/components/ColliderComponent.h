#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "dungeon/CollisionBox.h"
#include <SFML/Graphics/Rect.hpp>
#include <array>
#include <iostream>
#include <string>

struct ColliderComponent
{
    sf::RectangleShape mRectangle;
    CollisionBox::CollisionType mCollisionType;
    bool isHit{false};
    std::array<int, 4> coordOfForEveryCorner{};
    int damageTaken;
};

#endif// COLLIDERCOMPONENT_H
