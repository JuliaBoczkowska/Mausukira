#ifndef WANDER_H
#define WANDER_H
#include "SteeringBehaviourBase.h"

/** Agent wanders around the map randomly until it sees player */
class Wander : public SteeringBehaviourBase
{
public:
    explicit Wander(entt::registry& registry);
    sf::Vector2f getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                  PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent) override;

private:
    /** Radius of the circle in front of enemy*/
    float mWanderRadius{50};

    /** The distance of the circle projection */
    float mMaxAmountOfRandomDisplacement{5};

    float mWanderCircleProjectDistance{2};
    sf::Vector2f projectCircleInWorldSpace(
        const AiComponent& aiComponent, PositionComponent& positionComponent,
        SteeringBehaviourComponent& steeringBehaviourComponent) const;
};


#endif// WANDER_H
