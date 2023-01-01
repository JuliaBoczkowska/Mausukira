#ifndef COLLISIONSTATIC_H
#define COLLISIONSTATIC_H

#include "ecs/systems/System.h"
#include "SFML/Graphics/RectangleShape.hpp"

class ColliderComponent;

class MapContext;

class SpatialHash;

class CollisionStatic : public System
{
public:
    CollisionStatic(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid);

    void update(const sf::Time& dt) override;

private:
    void playerAndWallCollision(const sf::Time& dt);

    void bulletAndWallCollision(const sf::Time& time);

    bool checkIfIntersects(ColliderComponent& colliderComponent, const sf::Vector2f& futurePositionToCheck) const;

    bool isBulletOutOfBounds(const ColliderComponent& colliderComponent);

    bool isBulletCollidingWall(ColliderComponent& colliderComponent, sf::RectangleShape* const& collider);

private:
    MapContext& mMapContext;
    SpatialHash& mSpatialGrid;
};


#endif //COLLISIONSTATIC_H
