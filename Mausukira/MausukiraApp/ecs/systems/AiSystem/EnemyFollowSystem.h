#ifndef ENEMYFOLLOWSYSTEM_H
#define ENEMYFOLLOWSYSTEM_H

#include "ecs/systems/System.h"
#include "ecs/components/PositionComponent.h"


class EnemyFollowSystem : public System
{
    explicit EnemyFollowSystem(entt::registry& registry);

    void update(const sf::Time& dt) override;

    float minimumDistance{ 0 };

    float distance(PositionComponent component, sf::Vector2f vector2);
};


#endif //ENEMYFOLLOWSYSTEM_H
