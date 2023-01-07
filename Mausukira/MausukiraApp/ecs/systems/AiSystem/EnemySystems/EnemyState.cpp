#include "EnemyState.h"
#include "EnemyStateSystem.h"

EnemyState::EnemyState(EnemyStateSystem& stateHandler, SteeringBehaviour& steeringBehaviour,
                       entt::registry& registry)
    : mSteeringBehaviour(steeringBehaviour)
    , mSystemHandler(stateHandler)
    , mRegistry(registry)
{
}
