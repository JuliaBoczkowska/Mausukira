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
    MovableComponent() = default;
    MovableComponent(const MovableComponent&) = default;

    float mVelocity{1.f};
    float mVelocityMax;
    sf::Vector2f mSpeed;
    sf::Vector2f mAcceleration;
    Direction mDirection;
};


#endif// MOVABLECOMPONENT_H
