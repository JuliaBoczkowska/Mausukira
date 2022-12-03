#ifndef MOVABLECOMPONENT_H
#define MOVABLECOMPONENT_H


#include "SFML/System/Vector2.hpp"

class Direction;

struct MovableComponent
{
    MovableComponent() = default;

    MovableComponent(const MovableComponent&) = default;

    sf::Vector2f mVelocity;
    float mVelocityMax;
    sf::Vector2f mSpeed;
    sf::Vector2f mAcceleration;
    Direction* mDirection;
};


#endif// MOVABLECOMPONENT_H
