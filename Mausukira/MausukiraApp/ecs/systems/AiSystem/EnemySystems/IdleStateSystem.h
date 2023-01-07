#ifndef IDLESTATESYSTEM_H
#define IDLESTATESYSTEM_H

#include "EnemyState.h"

class IdleStateSystem : public EnemyState
{
public:
    IdleStateSystem(EnemyStateSystem& stateHandler, SteeringBehaviour& steeringBehaviour,
                    entt::registry& registry);

    sf::Vector2f update(const sf::Time& dt, entt::entity entity) override;
};


#endif// IDLESTATESYSTEM_H
