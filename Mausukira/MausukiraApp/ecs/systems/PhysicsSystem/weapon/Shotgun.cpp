#include "Shotgun.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/entities/Entity.h"
#include "utils/Math.h"

Shotgun::Shotgun(entt::registry& registry, sf::RenderWindow& window)
    : Weapon(registry, window)
{
    mWeaponDamage = 6;
    mWeaponDelay = 300;
    mAttackSpeed = 3;
    mProjectileColor = sf::Color::Green;
    mProjectileSize = 1;
}

void Shotgun::setupProjectile(const sf::Time& dt, entt::entity entity, sf::Vector2f& weaponPosition)
{
    std::array<float, 3> angles = {0.f, 15.f, -15.f};
    Entity projectile{mRegistry.create(), &mRegistry};
    for (auto i = 0; i < 3; ++i)
    {
        auto heading = mAimDirectionNormalized;
        projectile = {mRegistry.create(), &mRegistry};
        projectile.addComponent<PositionComponent>(weaponPosition);
        projectile.addComponent<ProjectileVelocityComponent>(rotateBy(angles[i], heading) *
                                                             mAttackSpeed);
        projectile.addComponent<ProjectileBody>(mProjectileSize);
        projectile.addComponent<ProjectileDamage>(mWeaponDamage);
        setupProjectileCollider(projectile, entity);
    }
}
