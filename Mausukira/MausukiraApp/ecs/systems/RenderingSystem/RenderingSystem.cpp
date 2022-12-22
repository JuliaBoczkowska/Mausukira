#include "RenderingSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/PlayerComponent.h"

RenderingSystem::RenderingSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{
}

void RenderingSystem::draw(sf::RenderWindow& window)
{
    mRegistry.view<SpriteComponent, ColliderComponent, HealthComponent>().each(
        [&](SpriteComponent& spriteComponent, ColliderComponent& colliderComponent,
            HealthComponent& healthComponent)
        {
            for (const auto& sprite: spriteComponent.mSprites)
            {
                window.draw(sprite);
            }
            healthComponent.draw(window);
            window.draw(colliderComponent.mRectangle);
        });
}
