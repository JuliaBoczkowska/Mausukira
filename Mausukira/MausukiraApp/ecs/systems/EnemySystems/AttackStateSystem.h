#ifndef ATTACKSTATESYSTEM_H
#define ATTACKSTATESYSTEM_H


#include "SFML/System/Time.hpp"
#include "entt/entity/registry.hpp"

class AttackStateSystem
{
public:
    explicit AttackStateSystem(entt::registry& registry);

    void update(const sf::Time& dt);

private:
    entt::registry& mRegistry;
};


#endif //ATTACKSTATESYSTEM_H
