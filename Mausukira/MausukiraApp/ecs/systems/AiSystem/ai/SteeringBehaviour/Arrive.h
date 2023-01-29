#ifndef ARRIVE_H
#define ARRIVE_H
#include "SteeringBehaviourBase.h"

/** Seeks a target which in my case is a player
 * and arrives at its position with 0 velocity
 * The arriving is done with a deceleration of the velocity */
class Arrive : public SteeringBehaviourBase
{

public:
    explicit Arrive(entt::registry& registry);
    sf::Vector2f getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                  PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent);
    void checkIfMaxSpeedIsExceeded(const SteeringBehaviourComponent& steeringBehaviourComponent,
                                   float& speed) const;
};

#endif// ARRIVE_H
