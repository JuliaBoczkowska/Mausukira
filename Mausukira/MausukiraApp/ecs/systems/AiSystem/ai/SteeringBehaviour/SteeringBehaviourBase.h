#ifndef STEERINGBEHAVIOURBASE_H
#define STEERINGBEHAVIOURBASE_H
#include "SFML/System/Vector2.hpp"
#include "ecs/components/AiComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/SteeringBehaviourComponent.h"
#include "entt/entt.hpp"

class SteeringBehaviourBase
{
public:
    explicit SteeringBehaviourBase(entt::registry& registry);
    virtual ~SteeringBehaviourBase()
    {
    }

    /** Calculate the steering force */
    virtual sf::Vector2f getSteeringForce(
        entt::entity otherEntity, AiComponent& aiComponent, PositionComponent& positionComponent,
        SteeringBehaviourComponent& steeringBehaviourComponent) = 0;

    entt::registry& mRegistry;
};
#endif// STEERINGBEHAVIOURBASE_H
