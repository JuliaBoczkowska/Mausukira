#include "Arrive.h"

sf::Vector2f Arrive::getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                      PositionComponent& positionComponent,
                                      SteeringBehaviourComponent& steeringBehaviourComponent)
{
    auto& playerPosition = aiComponent.mPlayerPositionComponent->mPosition;
    auto& enemyPosition = positionComponent.mPosition;
    auto& enemyVelocity = aiComponent.mVelocity->mVelocity;
    sf::Vector2f velocity{0, 0};
    const auto& vecPlayerTarget = playerPosition - enemyPosition;

    /** Obtain direction vector to the player. */
    float distanceToPlayer = calculateVectorLength(vecPlayerTarget);
    if (distanceToPlayer > 0)
    {
        float speed = distanceToPlayer / 20.f;
        checkIfMaxSpeedIsExceeded(steeringBehaviourComponent, speed);
        velocity = vecPlayerTarget * speed / distanceToPlayer;
        velocity = velocity - enemyVelocity;
    }
    return velocity;
}

void Arrive::checkIfMaxSpeedIsExceeded(const SteeringBehaviourComponent& steeringBehaviourComponent,
                                       float& speed) const
{
    if (speed > steeringBehaviourComponent.maxSpeed)
    {
        speed = steeringBehaviourComponent.maxSpeed;
    }
}

Arrive::Arrive(entt::registry& registry)
    : SteeringBehaviourBase(registry)
{
}
