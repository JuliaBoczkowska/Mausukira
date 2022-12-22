#include "ProjectileShootSystem.h"

ProjectileShootSystem::ProjectileShootSystem(entt::registry& registry)
    : System(registry)
{

}

void ProjectileShootSystem::handleInput(sf::Event& event)
{
    System::handleInput(event);
}

void ProjectileShootSystem::update(const sf::Time& dt)
{
    System::update(dt);
}

void ProjectileShootSystem::draw(sf::RenderWindow& window)
{
    System::draw(window);
}
