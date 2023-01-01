#ifndef COLLISIONKINEMATIC_H
#define COLLISIONKINEMATIC_H

#include "ecs/systems/System.h"
#include "ecs/components/ColliderComponent.h"

class MapContext;

class SpatialHash;

class CollisionKinematic : public System
{
public:
    explicit CollisionKinematic(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid);

    void projectileAndEnemyCollision();

    bool isColliderIntersectingEnemy(ColliderComponent& colliderComponent, ColliderComponent* collider) const;

    void update(const sf::Time& dt) override;

private:
    SpatialHash& mSpatialGrid;
    MapContext& mMapContext;
};


#endif //COLLISIONKINEMATIC_H
