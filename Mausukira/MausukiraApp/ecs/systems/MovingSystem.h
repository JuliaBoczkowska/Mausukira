#ifndef MOVINGSYSTEM_H
#define MOVINGSYSTEM_H
#include "System.h"

class PlayerMoveSystem : public System
{
public:
    PlayerMoveSystem(entt::registry& registry);
    void handleInput(sf::Event& event);
    void update(const sf::Time& dt);
    sf::Vector2f& preventHigherSpeedOnDiagonalMov(sf::Vector2f& velocity) const;
};


#endif// MOVINGSYSTEM_H
