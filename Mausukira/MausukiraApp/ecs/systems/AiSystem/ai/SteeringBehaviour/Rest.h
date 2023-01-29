#ifndef REST_H
#define REST_H
#include "SteeringBehaviourBase.h"

class Rest : public SteeringBehaviourBase
{

public:
    explicit Rest(entt::registry& registry);
    sf::Vector2f getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                  PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent) override;
};

#endif// REST_H
