#ifndef ENEMYSTATESYSTEM_H
#define ENEMYSTATESYSTEM_H

#include "ecs/systems/System.h"
#include "AttackStateSystem.h"
#include "IdleStateSystem.h"

class EnemyStateSystem : public System
{
public:
    explicit EnemyStateSystem(entt::registry& registry);

    void update(const sf::Time& dt) override;

    AttackStateSystem mAttackStateSystem;
    IdleStateSystem mIdleStateSystem;
};


#endif //ENEMYSTATESYSTEM_H
