#include "SensorSystem.h"


sf::Vector2f SensorSystem::update(const sf::Time& dt, entt::entity entity)
{
    updateEnemyVisionSensor();
    return sf::Vector2f{};
}

void SensorSystem::updateEnemyVisionSensor()
{
}
