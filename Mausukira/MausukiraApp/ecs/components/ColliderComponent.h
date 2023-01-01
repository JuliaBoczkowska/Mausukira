#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <array>
#include "dungeon/CollisionBox.h"
#include <iostream>

struct ColliderComponent
{
    sf::RectangleShape mRectangle;
    CollisionBox::CollisionType mCollisionType;
    std::array<int, 4> coordOfForEveryCorner{};
    bool isHit{ false };
};

#endif// COLLIDERCOMPONENT_H
