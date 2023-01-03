#ifndef ENEMYFOLLOWSYSTEM_H
#define ENEMYFOLLOWSYSTEM_H

#include "ecs/systems/System.h"


class EnemyFollowSystem : public System
{
    explicit EnemyFollowSystem(entt::registry& registry);

    void update(const sf::Time& dt) override;
};


#endif //ENEMYFOLLOWSYSTEM_H
