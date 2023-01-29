#ifndef COLLISIONSTATIC_H
#define COLLISIONSTATIC_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "ecs/systems/System.h"

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

    void whenEnemyTouchesPlayerCollision(const sf::Time& time);

    bool checkIfIntersects(ColliderComponent& colliderComponent,
                           const sf::Vector2f& futurePositionToCheck) const;

    bool isBulletOutOfBounds(const ColliderComponent& colliderComponent);

    bool isColliderAndRectShapeColliding(ColliderComponent& colliderComponent,
                                         sf::RectangleShape& collider);

    void playerAndDoorCollision();

private:
    MapContext& mMapContext;
    SpatialHash& mSpatialGrid;
    ColliderComponent* mPlayerFootCollider;
    ColliderComponent* mPlayerBodyCollider;
    void updateEnemyCollider();
};


#endif// COLLISIONSTATIC_H
