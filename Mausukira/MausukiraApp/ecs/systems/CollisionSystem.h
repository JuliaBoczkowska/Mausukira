#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
#include "SFML/Graphics/CircleShape.hpp"
#include "System.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/TransformComponent.h"
#include "scene/map/MapContext.h"

class CollisionSystem : public System
{
public:
    CollisionSystem(entt::registry& registry, MapContext& mapContext);
    void handleInput(sf::Event& event);
    void update(const sf::Time& dt);
    void draw(sf::RenderWindow& window) override;

    MapContext& mMapContext;
    bool checkIfAllowsToUpdatePosition(ColliderComponent& colliderComponent,
                                       const sf::Vector2f& futurePositionToCheck) const;

    sf::CircleShape shape;
};


#endif// COLLISIONSYSTEM_H
