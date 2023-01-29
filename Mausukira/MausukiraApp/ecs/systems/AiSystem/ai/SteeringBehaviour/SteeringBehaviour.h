#ifndef STEERINGBEHAVIOUR_H
#define STEERINGBEHAVIOUR_H


#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SteeringBehaviourBase.h"
#include "dungeon/map/Constants.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/SteeringBehaviourComponent.h"
#include "entt/entity/registry.hpp"
#include <list>
#include <memory>
#include <optional>

class MapContext;
class Tile;
class PositionComponent;
class ColliderComponent;
class AiComponent;

class SteeringBehaviour
{
    const float mWallAvoidanceWeight = 30.0f;
    const float mWanderWeight = 0.1f;
    const float mSeekWeight = 0.1f;
    const float mSeparationWeight = 7.0f;
    const float mRestWeight = 1.f;
    const float mFleeWeight = 0.4f;

public:
    SteeringBehaviour(MapContext& tileMap, entt::registry& registry);

    /** Calculate the steering force */
    sf::Vector2f getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                  PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent);

private:
    bool sumUpForces(sf::Vector2f& totalForce, sf::Vector2f forceToAdd, float maxForce);


    MapContext& mTileMap;
    std::vector<sf::RectangleShape*> collisions;
    entt::registry& mRegistry;
    std::unordered_map<EnemyBehaviour, std::unique_ptr<SteeringBehaviourBase>> mSteeringBehaviours;
};


#endif// STEERINGBEHAVIOUR_H
