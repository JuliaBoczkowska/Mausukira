#ifndef IDLESTATESYSTEM_H
#define IDLESTATESYSTEM_H

#include "EnemyState.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/EntityComponent.h"
class Enemy;
class SteeringBehaviourComponent;

class IdleStateSystem : public EnemyState
{
public:
    IdleStateSystem(EnemyStateSystem& stateHandler, SteeringBehaviour& steeringBehaviour,
                    entt::registry& registry);
    void whenEnemyIsHitByEnemyTriggerAttack(EntityStatistic& entityStatistic,
                                            SteeringBehaviourComponent& steering,
                                            EntityState& entityState, entt::entity entity);
    sf::Vector2f update(const sf::Time& dt, entt::entity entity) override;
    void whenPlayerIsInFovChangeState(EntityStatistic& entityStatistic, EntityState& entityState,
                                      const SensorComponent& sensorComponent,
                                      SteeringBehaviourComponent& steering) const;
    void changeIdleToAttackState(EntityStatistic& entityStatistic, EntityState& entityState,
                                 SteeringBehaviourComponent& steering) const;
};


#endif// IDLESTATESYSTEM_H
