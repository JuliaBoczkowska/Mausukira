#include "Rest.h"

Rest::Rest(entt::registry& registry)
    : SteeringBehaviourBase(registry)
{
}

sf::Vector2f Rest::getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                    PositionComponent& positionComponent,
                                    SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f velocity;
    if (steeringBehaviourComponent.clock.getElapsedTime().asSeconds() -
            steeringBehaviourComponent.restPointInTime >
        steeringBehaviourComponent.mRestTime)
    {
        velocity /= (steeringBehaviourComponent.deceleration * 5);
    }
    else
    {
        steeringBehaviourComponent.restPointInTime =
            steeringBehaviourComponent.clock.getElapsedTime().asSeconds();
        setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::WANDER);
        setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::WALL_AVOIDANCE);
        setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::SEPARATION);
    }
    return velocity;
}
