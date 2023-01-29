#ifndef SENSORSYSTEM_H
#define SENSORSYSTEM_H

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "dungeon/map/MapContext.h"
#include "ecs/entities/Entity.h"
#include "ecs/systems/System.h"

class SensorSystem : public System
{
public:
    const float mAiViewDistance = 25.f;
    const float mViewDistance = 25.f * 0.75f;
    SensorSystem(entt::registry& registry, MapContext& mapContext);
    void update(const sf::Time& dt);
    void draw(sf::RenderWindow& window);

private:
    void updateEnemyVisionSensor();
    bool isPlayerInEnemyFieldOfView(sf::Vector2f enemyPosition, sf::Vector2f facingDirectionVector,
                                    sf::Vector2f playerPosition, float fov);
    bool isLineOfSightCollidingWithWall(sf::Vector2f vector2, sf::Vector2f vector21);
    void setupConeOfSight();

private:
    float timeToEraseSensorMemory{5.f};
    entt::registry& mRegistry;
    MapContext& mMapContext;
};


#endif// SENSORSYSTEM_H
