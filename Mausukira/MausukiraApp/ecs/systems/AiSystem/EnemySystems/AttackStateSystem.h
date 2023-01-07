#ifndef ATTACKSTATESYSTEM_H
#define ATTACKSTATESYSTEM_H
#include "EnemyState.h"

class SteeringBehaviour;
class AttackStateSystem : public EnemyState
{
public:
    AttackStateSystem(EnemyStateSystem& stateHandler, SteeringBehaviour& steeringBehaviour,
                      entt::registry& registry);

    sf::Vector2f update(const sf::Time& dt, entt::entity entity) override;
};


#endif// ATTACKSTATESYSTEM_H
