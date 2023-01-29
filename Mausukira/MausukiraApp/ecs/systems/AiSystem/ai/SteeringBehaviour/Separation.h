#ifndef SEPARATION_H
#define SEPARATION_H
#include "SteeringBehaviourBase.h"

/** Separate enemies from each other*/
class Separation : public SteeringBehaviourBase
{
public:
    explicit Separation(entt::registry& registry);
    sf::Vector2f getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                  PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent) override;
};

#endif// SEPARATION_H
