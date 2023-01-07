#ifndef IDLESTATESYSTEM_H
#define IDLESTATESYSTEM_H

#include "SFML/System/Time.hpp"
#include "entt/entity/registry.hpp"

class IdleStateSystem
{
public:
    IdleStateSystem(entt::registry& registry)
        : mRegistry(registry)
    {

    }

    void update(const sf::Time& dt);

private:
    entt::registry& mRegistry;
};


#endif //IDLESTATESYSTEM_H
