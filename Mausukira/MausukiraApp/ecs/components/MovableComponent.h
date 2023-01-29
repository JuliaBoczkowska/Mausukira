#ifndef MOVABLECOMPONENT_H
#define MOVABLECOMPONENT_H

#include "SFML/System/Vector2.hpp"

enum class Direction
{
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    DOWN = 3
};

struct MovableComponent
{
    int id;
};

#endif// MOVABLECOMPONENT_H
