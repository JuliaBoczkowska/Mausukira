#ifndef PLAYERMOVESYSTEM_H
#define PLAYERMOVESYSTEM_H

#include "ecs/systems/System.h"
#include "ecs/components/MovableComponent.h"

class PlayerMoveSystem : public System
{
public:
    PlayerMoveSystem(entt::registry& registry);

    void handleInput(sf::Event& event);

    void update(const sf::Time& dt);

    sf::Vector2f& preventHigherSpeedOnDiagonalMov(sf::Vector2f& velocity) const;

    void handlePlayerBasicMovement(float speed, sf::Vector2f& velocity, Direction& direction) const;

    void handlePlayerDash(const sf::Event& event);

private:
    float mDashSpeed{ 1.f };
};


#endif// PLAYERMOVESYSTEM_H
