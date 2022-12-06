#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
#include "System.h"
#include "scene/map/MapContext.h"

class CollisionSystem : public System
{
public:
    CollisionSystem(entt::registry& registry, MapContext& mapContext);
    void handleInput(sf::Event& event);
    void update(const sf::Time& dt);

    MapContext& mMapContext;
};


#endif// COLLISIONSYSTEM_H
