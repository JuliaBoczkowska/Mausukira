#include "IdleStateSystem.h"
#include "ai/SteeringBehaviour.h"
#include "ecs/components/AiComponent.h"
#include "SensorSystem.h"
IdleStateSystem::IdleStateSystem(EnemyStateSystem& stateHandler,
                                 SteeringBehaviour& steeringBehaviour, entt::registry& registry)
    : EnemyState(stateHandler, steeringBehaviour, registry)
{
}

sf::Vector2f IdleStateSystem::update(const sf::Time& dt, entt::entity entity)
{
    AiComponent& aiComponent = mRegistry.get<AiComponent>(entity);
    PositionComponent& positionComponent = mRegistry.get<PositionComponent>(entity);
    SteeringBehaviourComponent& steering =
        mRegistry.template get<SteeringBehaviourComponent>(entity);

    return mSteeringBehaviour.getSteeringForce(aiComponent, positionComponent, steering);
}
