#include "Separation.h"

Separation::Separation(entt::registry& registry)
    : SteeringBehaviourBase(registry)
{
}
sf::Vector2f Separation::getSteeringForce(
    entt::entity otherEntity, AiComponent& otherAiComponent,
    PositionComponent& otherPositionComponent,
    SteeringBehaviourComponent& otherSteeringBehaviourComponent)
{
    sf::Vector2f force{};
    mRegistry.view<PositionComponent, SteeringBehaviourComponent>().each(
        [&](auto entity, PositionComponent& positionComponent, SteeringBehaviourComponent& steering)
        {
            if (entity != otherEntity)
            {
                if (steering.isInCloseDistanceWithOtherEnemy)
                {
                    sf::Vector2f vecEnemyToEnemy =
                        otherPositionComponent.mPosition - positionComponent.mPosition;
                    force +=
                        normalizeVector(vecEnemyToEnemy) / calculateVectorLength(vecEnemyToEnemy);
                }
            }
        });
    return force;
}
