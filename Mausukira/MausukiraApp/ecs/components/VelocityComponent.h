#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include "SFML/System/Vector2.hpp"

struct VelocityComponent
{
    /** Maximum velocity of the enemy unit */
    sf::Vector2f mVelocity{0.f, 0.f};
};


struct ProjectileVelocityComponent
{
    /** Maximum velocity of the enemy unit */
    sf::Vector2f mVelocity{0.f, 0.f};
};


#endif// VELOCITYCOMPONENT_H
