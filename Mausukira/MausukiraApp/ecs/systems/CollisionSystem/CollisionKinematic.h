#ifndef COLLISIONKINEMATIC_H
#define COLLISIONKINEMATIC_H

#include "ecs/systems/System.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/systems/SpatialHashing/SpatialHash.h"

class MapContext;

class CollisionKinematic : public System
{
public:
    explicit CollisionKinematic(entt::registry& registry, MapContext& mapContext);

    void projectileAndEnemyCollision(const sf::Time& dt);

    bool isIntersectingEnemy() const;

    void update(const sf::Time& dt) override;

private:
    SpatialHash mSpatialGrid;
    MapContext& mMapContext;
};


#endif //COLLISIONKINEMATIC_H
