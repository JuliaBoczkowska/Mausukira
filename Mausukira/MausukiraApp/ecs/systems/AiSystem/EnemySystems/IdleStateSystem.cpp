#include "IdleStateSystem.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/entities/enemy/Enemy.h"
#include "ecs/systems/AiSystem/ai/SensorSystem.h"
#include "ecs/systems/AiSystem/ai/SteeringBehaviour/SteeringBehaviour.h"

IdleStateSystem::IdleStateSystem(EnemyStateSystem& stateHandler,
                                 SteeringBehaviour& steeringBehaviour, entt::registry& registry)
    : EnemyState(stateHandler, steeringBehaviour, registry)
{
}

void IdleStateSystem::whenEnemyIsHitByEnemyTriggerAttack(EntityStatistic& entityStatistic,
                                                         SteeringBehaviourComponent& steering,
                                                         EntityState& entityState,
                                                         entt::entity entity)
{
    auto& relationship = mRegistry.get<Relationship>(entity);
    auto& comp = mRegistry.get<Relationship>(entity);
    auto curr = comp.first_child;

    while (curr != entt::null)
    {
        auto& colliderComponent = mRegistry.get<ColliderComponent>(curr);
        if (colliderComponent.isHit)
        {
            changeIdleToAttackState(entityStatistic, entityState, steering);
        }
        curr = mRegistry.get<Relationship>(curr).next;
    }
}

sf::Vector2f IdleStateSystem::update(const sf::Time& dt, entt::entity entity)
{
    AiComponent& aiComponent = mRegistry.get<AiComponent>(entity);
    EntityState& entityState = mRegistry.get<EntityState>(entity);
    PositionComponent& positionComponent = mRegistry.get<PositionComponent>(entity);
    SteeringBehaviourComponent& steering = mRegistry.get<SteeringBehaviourComponent>(entity);
    SensorComponent& sensorComponent = mRegistry.get<SensorComponent>(entity);
    EntityStatistic& entityStatistic = mRegistry.get<EntityStatistic>(entity);

    whenEnemyIsHitByEnemyTriggerAttack(entityStatistic, steering, entityState, entity);
    whenPlayerIsInFovChangeState(entityStatistic, entityState, sensorComponent, steering);

    return mSteeringBehaviour.getSteeringForce(entity, aiComponent, positionComponent, steering);
}

void IdleStateSystem::whenPlayerIsInFovChangeState(EntityStatistic& entityStatistic,
                                                   EntityState& entityState,
                                                   const SensorComponent& sensorComponent,
                                                   SteeringBehaviourComponent& steering) const
{
    if (sensorComponent.mIsPlayerInFieldOfView)
    {
        changeIdleToAttackState(entityStatistic, entityState, steering);
    }
}

void IdleStateSystem::changeIdleToAttackState(EntityStatistic& entityStatistic,
                                              EntityState& entityState,
                                              SteeringBehaviourComponent& steering) const
{
    entityState.state = MobState::Attacking;
    clearFlag(steering.mBehaviourFlag);
    setFlagOn(steering.mBehaviourFlag, ARRIVE);
    setFlagOn(steering.mBehaviourFlag, WALL_AVOIDANCE);
    setFlagOn(steering.mBehaviourFlag, SEPARATION);
    if (entityStatistic.mAttackType == AttackType::Ranged)
    {
        setFlagOn(steering.mBehaviourFlag, FLEE);
    }
}
