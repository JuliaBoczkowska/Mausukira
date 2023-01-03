#include "MoveSystem.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/components/AttachmentPoint.h"

MoveSystem::MoveSystem(entt::registry& registry)
    : System(registry)
    , mPlayerMoveSystem(registry)
{
    mRegistry.view<SpriteComponent, HealthComponent, PositionComponent>().each(
        [&](SpriteComponent& spriteComponent,
            HealthComponent& healthComponent, PositionComponent& positionComponent)
        {
            const auto& position = positionComponent.mPosition;
            for (auto& sprite: spriteComponent.mSprites)
            {
                sprite.setPosition(position);
            }
            healthComponent.setPosition(position);
        });
}

void MoveSystem::handleInput(sf::Event& event)
{
    mPlayerMoveSystem.handleInput(event);
}

void MoveSystem::update(const sf::Time& dt)
{
    mPlayerMoveSystem.update(dt);

    // projectile
    mRegistry.view<ProjectileBody, PositionComponent, VelocityComponent>().each(
        [&](ProjectileBody& projectileBody,
            PositionComponent& positionComponent, VelocityComponent velocityComponent)
        {
            positionComponent.mPosition += (velocityComponent.mVelocity * dt.asSeconds());
        });

    // weapon
    auto group = mRegistry.group<AttachmentPoint>(entt::get<WeaponComponent, PositionComponent>);
    for (auto entity: group)
    {
        auto [attachmentPoint, weapon, weaponPosition] = group.get(entity);
        auto parent = attachmentPoint.parent;

        auto& positionParent = mRegistry.get<PositionComponent>(parent).mPosition;
        weaponPosition.mPosition = positionParent + attachmentPoint.offsetFromParent;
    }
}

void MoveSystem::postUpdate()
{
    mRegistry.view<SpriteComponent, HealthComponent, PositionComponent>().each(
        [&](SpriteComponent& spriteComponent,
            HealthComponent& healthComponent, PositionComponent& positionComponent)
        {
            const auto& position = positionComponent.mPosition;
            healthComponent.setPosition(position);
            for (auto& sprite: spriteComponent.mSprites)
            {
                sprite.setPosition(position);
            }
        });

    mRegistry.view<ProjectileBody, PositionComponent>().each(
        [&](ProjectileBody& projectileBody,
            PositionComponent& positionComponent)
        {
            projectileBody.mProjectile.setPosition(positionComponent.mPosition);
        });

    mRegistry.view<WeaponComponent, PositionComponent>().each(
        [&](WeaponComponent& weaponComponent,
            PositionComponent& positionComponent)
        {
            weaponComponent.mWeapon.setPosition(positionComponent.mPosition);
        });
}
