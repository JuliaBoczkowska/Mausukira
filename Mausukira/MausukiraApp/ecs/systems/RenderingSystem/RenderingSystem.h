#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include "ecs/systems/System.h"
#include "dungeon/map/MapContext.h"

class RenderingSystem : public System
{
public:
    RenderingSystem(entt::registry& registry, MapContext& mapContext);

    void draw(sf::RenderWindow& window) override;

    void sortSprites();

private:
    MapContext& mMapContext;
};

#endif// RENDERINGSYSTEM_H
