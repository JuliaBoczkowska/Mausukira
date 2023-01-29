#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include "dungeon/map/MapContext.h"
#include "ecs/systems/System.h"

class RenderingSystem : public System
{
public:
    RenderingSystem(entt::registry& registry, MapContext& mapContext);

    void draw(sf::RenderWindow& window) override;

private:
    MapContext& mMapContext;
};

#endif// RENDERINGSYSTEM_H
