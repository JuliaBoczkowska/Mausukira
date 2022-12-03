#ifndef SYSTEM_H
#define SYSTEM_H

#include "SFML/Window/Event.hpp"
#include "entt/entity/registry.hpp"

class System
{
public:
    explicit System(entt::registry& registry)
        : mRegistry(registry)
    {
    }

    virtual void handleInput(sf::Event& event) = 0;

    virtual void update(const sf::Time& dt) = 0;

    entt::registry& mRegistry;
};


#endif// SYSTEM_H
