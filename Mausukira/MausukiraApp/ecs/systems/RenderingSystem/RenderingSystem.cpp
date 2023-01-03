#include "RenderingSystem.h"
#include "ecs/components/Components.h"


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
            window.draw(healthComponent.mHealthBarOutline);
            window.draw(healthComponent.mHealthBarRect);
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

    mRegistry.view<ScoreComponent>().each(
        [&](ScoreComponent& scoreComponent)
        {
            auto oldView = window.getView();
            window.setView(window.getDefaultView());
            window.draw(scoreComponent.counter);
            window.draw(scoreComponent.rectangle);

            window.setView(oldView);
        });

    mRegistry.view<DoorBodyComponent>().each(
        [&](DoorBodyComponent& doorBodyComponent)
        {
            window.draw(doorBodyComponent.doorShape);
        });
}
