#include "SensorSystem.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/SteeringBehaviourComponent.h"

SensorSystem::SensorSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mRegistry(registry)
    , mMapContext(mapContext)
{
}

void SensorSystem::update(const sf::Time& dt)
{
    updateEnemyVisionSensor();
}

void SensorSystem::updateEnemyVisionSensor()
{
    mRegistry.view<SensorComponent, AiComponent, PositionComponent, SteeringBehaviourComponent>()
        .each(
            [&](SensorComponent& sensorComponent, AiComponent& aiComponent,
                PositionComponent& positionComponent,
                SteeringBehaviourComponent& steeringBehaviourComponent)
            {
                if (isPlayerInEnemyFieldOfView(positionComponent.mPosition,
                                               steeringBehaviourComponent.mDirectionVector,
                                               aiComponent.mPlayerPositionComponent->mPosition,
                                               sensorComponent.fieldOfView))
                {
                    /** Cast a ray from enemy to player to see if anything is on the path between
                     * them */
                    if (!isLineOfSightCollidingWithWall(
                            positionComponent.mPosition,
                            aiComponent.mPlayerPositionComponent->mPosition))
                    {
                        sensorComponent.mIsPlayerInFieldOfView = true;
                    }
                }
            });
}

bool SensorSystem::isPlayerInEnemyFieldOfView(sf::Vector2f enemyPosition,
                                              sf::Vector2f facingDirectionVector,
                                              sf::Vector2f playerPosition, float fov)
{

    /** Comparing angle of the sight cone with angle between facing vector enemy player position */
    sf::Vector2f vecEnemyPlayer = normalizeVector(playerPosition - enemyPosition);

    return (dotProduct(facingDirectionVector, vecEnemyPlayer) >= cos(fov / 2.0));
}

bool SensorSystem::isLineOfSightCollidingWithWall(sf::Vector2f vectorA, sf::Vector2f vectorB)
{

    for (auto wall: mMapContext.noTraversableTiles)
    {
        if (lineIntersectsRectangle(wall->mRectangle.getGlobalBounds(), vectorA, vectorB))
        {
            return true;
        }
    }
    return false;
}

void SensorSystem::draw(sf::RenderWindow& window)
{
}
