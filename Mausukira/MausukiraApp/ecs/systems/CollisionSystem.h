#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
#include "System.h"

class CollisionSystem : public System
{
public:
    CollisionSystem(entt::registry& registry);
    void handleInput(sf::Event& event);
    void update(const sf::Time& dt);
};


#endif// COLLISIONSYSTEM_H
