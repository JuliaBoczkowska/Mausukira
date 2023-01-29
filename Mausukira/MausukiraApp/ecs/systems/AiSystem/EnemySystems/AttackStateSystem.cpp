#include "AttackStateSystem.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/SteeringBehaviourComponent.h"
#include "ecs/systems/AiSystem/ai/SteeringBehaviour/SteeringBehaviour.h"

AttackStateSystem::AttackStateSystem(EnemyStateSystem& stateHandler,
                                     SteeringBehaviour& steeringBehaviour, entt::registry& registry)
    : EnemyState(stateHandler, steeringBehaviour, registry)
{
}

sf::Vector2f AttackStateSystem::update(const sf::Time& dt, entt::entity entity)
{
    AiComponent& aiComponent = mRegistry.get<AiComponent>(entity);
    PositionComponent& positionComponent = mRegistry.get<PositionComponent>(entity);
    SteeringBehaviourComponent& steering =
        mRegistry.template get<SteeringBehaviourComponent>(entity);
    SensorComponent& sensorComponent = mRegistry.get<SensorComponent>(entity);
    EntityState& entityState = mRegistry.get<EntityState>(entity);

    auto force =
        mSteeringBehaviour.getSteeringForce(entity, aiComponent, positionComponent, steering);
    if (sensorComponent.clock.getElapsedTime().asSeconds() -
            sensorComponent.mTimePlayerWasLastSeen <
        200)
    {
        entityState.state = MobState::Idle;
        clearFlag(steering.mBehaviourFlag);
        setFlagOn(steering.mBehaviourFlag, WALL_AVOIDANCE);
        setFlagOn(steering.mBehaviourFlag, SEPARATION);
        setFlagOn(steering.mBehaviourFlag, WANDER);
    }
    return force;
}