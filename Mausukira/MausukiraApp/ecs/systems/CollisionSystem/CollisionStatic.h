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

    void playerAndWallCollision(const sf::Time& dt);

    bool checkIfAllowsToUpdatePosition(ColliderComponent& colliderComponent,
        const sf::Vector2f& futurePositionToCheck) const;

    MapContext& mMapContext;

    void bulletAndWallCollision(const sf::Time& time);
};


#endif //COLLISIONSTATIC_H
