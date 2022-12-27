#include "RenderingSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/ShootingComponents.h"

RenderingSystem::RenderingSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{
}

void RenderingSystem::draw(sf::RenderWindow& window)
{
    mRegistry.view<SpriteComponent, HealthComponent>().each(
        [&](SpriteComponent& spriteComponent,
            HealthComponent& healthComponent)
        {
            for (const auto& sprite: spriteComponent.mSprites)
            {
                window.draw(sprite);
            }
            healthComponent.draw(window);
        });

    mRegistry.view<ColliderComponent>().each(
        [&](ColliderComponent& colliderComponent)
        {
            window.draw(colliderComponent.mRectangle);
        });

    mRegistry.view<ProjectileBody>().each(
        [&](ProjectileBody& projectileBody)
        {
            window.draw(projectileBody.mProjectile);
        });

    mRegistry.view<WeaponComponent>().each(
        [&](WeaponComponent& weaponComponent)
        {
            window.draw(weaponComponent.mWeapon);
        });
}
