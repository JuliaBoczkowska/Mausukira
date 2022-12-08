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
};


#endif// PLAYERMOVESYSTEM_H