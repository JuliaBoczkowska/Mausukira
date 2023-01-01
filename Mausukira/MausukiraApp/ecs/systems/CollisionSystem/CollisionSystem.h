#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "SFML/Graphics/CircleShape.hpp"
#include "ecs/systems/System.h"
#include "ecs/components/ColliderComponent.h"
#include "dungeon/map/MapContext.h"
#include "CollisionKinematic.h"
#include "CollisionStatic.h"

class CollisionBox;

class CollisionSystem : public System
{
public:
    CollisionSystem(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid);

    void update(const sf::Time& dt);

    void postUpdate() override;

private:
    CollisionKinematic mCollisionKinematic;
    CollisionStatic mCollisionStatic;
    MapContext& mMapContext;
    SpatialHash& mSpatialGrid;
};


#endif// COLLISIONSYSTEM_H
