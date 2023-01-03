#include "EnemyFollowSystem.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/PositionComponent.h"

EnemyFollowSystem::EnemyFollowSystem(entt::registry& registry)
    : System(registry)
{

}

void EnemyFollowSystem::update(const sf::Time& dt)
{
    mRegistry.view<AiComponent, PositionComponent>().each(
        [&](AiComponent& aiComponent, PositionComponent positionComponent)
        {
            if (distance(positionComponent, aiComponent.mPlayerPositionComponent->mPosition) > minimumDistance)
            {


            }
        });

}

float EnemyFollowSystem::distance(PositionComponent component, sf::Vector2f vector2)
{
    return 0;
}
