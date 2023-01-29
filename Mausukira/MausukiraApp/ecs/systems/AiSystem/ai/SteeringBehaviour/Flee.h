#ifndef FLEE_H
#define FLEE_H
#include "SteeringBehaviourBase.h"

class Flee : public SteeringBehaviourBase
{

public:
    Flee(entt::registry& registry);
    sf::Vector2f getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                  PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent) override;
};


#endif// FLEE_H
