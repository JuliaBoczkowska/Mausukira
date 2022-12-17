#ifndef PLAYERMOVESYSTEM_H
#define PLAYERMOVESYSTEM_H
#include "System.h"
#include "ecs/components/MovableComponent.h"

class PlayerMoveSystem : public System
{
public:
    PlayerMoveSystem(entt::registry& registry);
    void handleInput(sf::Event& event);
    void update(const sf::Time& dt);
    sf::Vector2f& preventHigherSpeedOnDiagonalMov(sf::Vector2f& velocity) const;
    void handlePlayerBasicMovement(float speed, sf::Vector2f& velocity, Direction& direction) const;
};


#endif// PLAYERMOVESYSTEM_H
