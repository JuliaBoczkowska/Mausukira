#ifndef PLAYERMOVESYSTEM_H
#define PLAYERMOVESYSTEM_H

#include "ecs/systems/System.h"
#include "ecs/components/MovableComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/components/PositionComponent.h"

class PlayerMoveSystem : public System
{
    /** PI value used for calculations */
    const double M_PI = 3.14159265358979323846264338327;

    /** The duration of the dash in seconds */
    const float DASH_DURATION = 3.f;
    /** The speed at which the player will dash */
    const float DASH_SPEED = 6.f;
public:

    PlayerMoveSystem(entt::registry& registry);

    void handleInput(sf::Event& event);

    void update(const sf::Time& dt);

    sf::Vector2f& preventHigherSpeedOnDiagonalMov(sf::Vector2f& velocity) const;

    void handlePlayerBasicMovement(float speed, sf::Vector2f& velocity, Direction& direction) const;

    void handlePlayerDash(const sf::Event& event);

    /** A timer to keep track of how long the dash has been active */
    float dashTimer;

    void
    performDash(const sf::Time& dt, const VelocityComponent& velocityComponent, PositionComponent& positionComponent);
};


#endif// PLAYERMOVESYSTEM_H
