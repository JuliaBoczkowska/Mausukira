#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SFML/Graphics/Rect.hpp>
#include <string>
#include "dungeon/CollisionBox.h"

struct ColliderComponent
{
    sf::RectangleShape mRectangle;
};

#endif// COLLIDERCOMPONENT_H
