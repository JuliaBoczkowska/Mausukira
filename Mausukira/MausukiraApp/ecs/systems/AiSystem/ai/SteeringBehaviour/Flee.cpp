#include "Flee.h"

Flee::Flee(entt::registry& registry)
    : SteeringBehaviourBase(registry)
{
}
sf::Vector2f Flee::getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                    PositionComponent& positionComponent,
                                    SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f velocity(0, 0);
    const double safeDistance = 120.0;
    if (calculateVectorsLength(positionComponent.mPosition,
                               aiComponent.mPlayerPositionComponent->mPosition) > safeDistance)
    {
        return velocity;
    }
    velocity = normalizeVector(positionComponent.mPosition -
                               aiComponent.mPlayerPositionComponent->mPosition) *
               steeringBehaviourComponent.maxSpeed;
    return (velocity - aiComponent.mVelocity->mVelocity);
}
