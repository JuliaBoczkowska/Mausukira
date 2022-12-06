#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H
#include "System.h"
#include "scene/map/MapContext.h"

class RenderingSystem : public System
{
public:
    RenderingSystem(entt::registry& registry, MapContext& mapContext);

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    void sortSprites();

private:
    MapContext& mMapContext;
};

#endif// RENDERINGSYSTEM_H
