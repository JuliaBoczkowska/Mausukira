#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <set>
#include "dungeon/CollisionBox.h"

struct ColliderComponent
{
    sf::RectangleShape mRectangle;
    CollisionBox::CollisionType mCollisionType;
    std::set<std::pair<int, int>> uniqueCellIndex;
};

#endif// COLLIDERCOMPONENT_H
