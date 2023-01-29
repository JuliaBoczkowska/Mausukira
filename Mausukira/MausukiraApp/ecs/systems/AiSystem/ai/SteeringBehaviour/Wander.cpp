#include "Wander.h"

Wander::Wander(entt::registry& registry)
    : SteeringBehaviourBase(registry)
{
}

sf::Vector2f Wander::getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                      PositionComponent& positionComponent,
                                      SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f force;
    /** Add random displacement */
    auto rndX = generateFloatNumberInRange(-1, 1);
    auto rndY = generateFloatNumberInRange(-1, 1);
    sf::Vector2f temp(rndX, rndY);
    aiComponent.mWanderPoint += temp * mMaxAmountOfRandomDisplacement;

    /** Make a unit vector */
    aiComponent.mWanderPoint = normalizeVector(aiComponent.mWanderPoint);

    /** Make the length of the vector the same as radius */
    aiComponent.mWanderPoint *= mWanderRadius;

    sf::Vector2f targetPointWorldSpace =
        projectCircleInWorldSpace(aiComponent, positionComponent, steeringBehaviourComponent);

    steeringBehaviourComponent.newPoint = targetPointWorldSpace;
    force = targetPointWorldSpace - positionComponent.mPosition;
    force = normalizeVector(force);
    return force;
}
sf::Vector2f Wander::projectCircleInWorldSpace(
    const AiComponent& aiComponent, PositionComponent& positionComponent,
    SteeringBehaviourComponent& steeringBehaviourComponent) const
{
    sf::Vector2f targetLocal =
        aiComponent.mWanderPoint + sf::Vector2f{mWanderCircleProjectDistance, 0};

    sf::Vector2f pointWorldSpace = localSpaceToWorldSpace(
        targetLocal, steeringBehaviourComponent.mDirectionVector,
        steeringBehaviourComponent.mSideVectorToDirection, positionComponent.mPosition);
    return pointWorldSpace;
}
