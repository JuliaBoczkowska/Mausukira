#ifndef PLAYERMOVESYSTEM_H
#define PLAYERMOVESYSTEM_H

#include "ecs/systems/System.h"
#include "ecs/components/MovableComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/components/PositionComponent.h"

class PlayerMoveSystem : public System
{
    /** The duration of the dash in seconds */
    const float DASH_DURATION = 0.5f;
    /** The speed at which the player will dash */
    const float DASH_SPEED = 6.f;

public:
    PlayerMoveSystem(entt::registry& registry);

    void handleInput(sf::Event& event);

    void update(const sf::Time& dt);

    sf::Vector2f& preventHigherSpeedOnDiagonalMov(sf::Vector2f& velocity) const;

    void handlePlayerBasicMovement(float speed, sf::Vector2f& velocity, Direction& direction) const;

    void handlePlayerDash(const sf::Event& event);

    void performDash(const sf::Time& dt, VelocityComponent& velocityComponent, PositionComponent& positionComponent);

    /** A timer to keep track of how long the dash has been active */
    float dashTimer;
};


#endif// PLAYERMOVESYSTEM_H
