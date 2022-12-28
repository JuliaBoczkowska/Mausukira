#ifndef COLLISIONSTATIC_H
#define COLLISIONSTATIC_H

#include "ecs/systems/System.h"

class ColliderComponent;

class MapContext;

class CollisionStatic : public System
{
public:
    CollisionStatic(entt::registry& registry, MapContext& mapContext);

    void update(const sf::Time& dt) override;

private:
    void playerAndWallCollision(const sf::Time& dt);

    void bulletAndWallCollision(const sf::Time& time);

    bool checkIfIntersects(ColliderComponent& colliderComponent, const sf::Vector2f& futurePositionToCheck) const;

private:
    MapContext& mMapContext;
};


#endif //COLLISIONSTATIC_H
