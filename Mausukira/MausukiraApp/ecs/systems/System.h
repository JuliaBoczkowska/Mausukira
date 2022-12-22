#ifndef SYSTEM_H
#define SYSTEM_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "entt/entity/registry.hpp"


class System
{
public:
    explicit System(entt::registry& registry)
        : mRegistry(registry)
    {
    }

    virtual void handleInput(sf::Event& event)
    {
    }

    virtual void update(const sf::Time& dt)
    {
    }

    virtual void postUpdate()
    {
    }

    virtual void draw(sf::RenderWindow& window)
    {
    }

    entt::registry& mRegistry;
};


#endif// SYSTEM_H
