#ifndef SENSORSYSTEM_H
#define SENSORSYSTEM_H

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "ecs/entities/Entity.h"

class SensorSystem
{
    sf::Vector2f update(const sf::Time& dt, entt::entity entity);

    void updateEnemyVisionSensor();
    float timeToEraseSensorMemory {5.f};
};


#endif// SENSORSYSTEM_H
