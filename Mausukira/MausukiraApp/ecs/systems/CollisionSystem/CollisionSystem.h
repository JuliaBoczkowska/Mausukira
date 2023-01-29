#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "CollisionKinematic.h"
#include "CollisionStatic.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "dungeon/map/MapContext.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/systems/System.h"

class CollisionBox;

class CollisionSystem : public System
{
public:
    CollisionSystem(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid);

    void update(const sf::Time& dt);

    void postUpdate() override;

private:
    void removeEnemyFromMap();
    void removeProjectileFromMap();
    void updateSpatialGrid();
    void handleEntitiesRemovalAfterCollision();

private:
    CollisionKinematic mCollisionKinematic;
    CollisionStatic mCollisionStatic;
    MapContext& mMapContext;
    SpatialHash& mSpatialGrid;
};


#endif// COLLISIONSYSTEM_H
