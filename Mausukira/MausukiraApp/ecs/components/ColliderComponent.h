#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SFML/Graphics/Rect.hpp>
#include <string>
#include "dungeon/CollisionBox.h"

struct ColliderComponent
{
    sf::RectangleShape mRectangle;
    CollisionBox::CollisionType mCollisionType;
};

#endif// COLLIDERCOMPONENT_H
