#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H
#include "../components/SpriteComponent.h"
#include "System.h"

class RenderingSystem : public System
{
public:
    RenderingSystem(entt::registry& registry);

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    void sortSprites();
};


#endif// RENDERINGSYSTEM_H
