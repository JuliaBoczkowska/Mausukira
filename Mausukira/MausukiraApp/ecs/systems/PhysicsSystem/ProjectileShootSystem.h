#ifndef PROJECTILESHOOTSYSTEM_H
#define PROJECTILESHOOTSYSTEM_H

#include "ecs/systems/System.h"
#include "states_stack/SharedContext.h"

class ProjectileShootSystem : public System
{
    ProjectileShootSystem(entt::registry& registry);

    void handleInput(sf::Event& event) override;

    void update(const sf::Time& dt) override;

    void draw(sf::RenderWindow& window) override;
};

#endif //PROJECTILESHOOTSYSTEM_H
