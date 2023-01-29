#ifndef COLLISIONKINEMATIC_H
#define COLLISIONKINEMATIC_H

#include "ecs/components/ColliderComponent.h"
#include "ecs/systems/System.h"

class MapContext;

class SpatialHash;

class CollisionKinematic : public System
{
public:
    explicit CollisionKinematic(entt::registry& registry, MapContext& mapContext,
                                SpatialHash& spatialGrid);

    void projectileAndEnemyCollision();

    bool isColliderIntersectingEnemy(ColliderComponent& colliderComponent,
                                     ColliderComponent* collider) const;
    bool isProjectileIntersectingHero(ColliderComponent& colliderComponent,
                                      ColliderComponent* collider) const;

    void update(const sf::Time& dt) override;

private:
    SpatialHash& mSpatialGrid;
    MapContext& mMapContext;
};


#endif// COLLISIONKINEMATIC_H
