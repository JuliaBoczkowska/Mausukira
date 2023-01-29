#include "Weapon.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/entities/Entity.h"
#include "utils/Math.h"


Weapon::Weapon(entt::registry& registry, sf::RenderWindow& window)
    : mRegistry(registry)
{
}
void Weapon::adjustWeaponRotation(WeaponComponent& weaponComponent, sf::Vector2f& weaponPosition,
                                  sf::Vector2f& aimTarget)
{
    auto aimDirection = aimTarget - weaponPosition;
    mAimDirectionNormalized = normalizeVector(aimDirection);
    setWeaponRotation(aimDirection, weaponComponent);
}

void Weapon::setWeaponRotation(const sf::Vector2f& aimDirection,
                               WeaponComponent& weaponComponent) const
{
    weaponComponent.mWeapon.setRotation(180 - getRotationAngleInRadians(aimDirection));
}

void Weapon::setupProjectile(const sf::Time& dt, entt::entity entity, sf::Vector2f& weaponPosition)
{
    Entity projectile{mRegistry.create(), &mRegistry};
    projectile.addComponent<PositionComponent>(weaponPosition);
    projectile.addComponent<ProjectileVelocityComponent>(mAimDirectionNormalized * 4.f);
    projectile.addComponent<ProjectileBody>(mProjectileSize, mProjectileColor);
    projectile.addComponent<ProjectileDamage>(mWeaponDamage);

    setupProjectileCollider(projectile, entity);
}

void Weapon::setupProjectileCollider(Entity& projectile, entt::entity entity)
{
    Entity colliderProjectile{mRegistry.create(), &mRegistry};
    sf::RectangleShape rect(CollisionBox::setupCollider(
        projectile.getComponent<ProjectileBody>().mProjectile.getGlobalBounds(),
        CollisionBox::CollisionType::PROJECTILE));
    colliderProjectile.addComponent<ColliderComponent>(rect,
                                                       CollisionBox::CollisionType::PROJECTILE);
    colliderProjectile.addComponent<AttachmentPoint>(projectile.getEntity());

    if (mRegistry.any_of<WeaponEnemy>(entity))
    {
        colliderProjectile.addComponent<EnemyProjectileCollider>(entity);
        colliderProjectile.addComponent<ProjectileCollider>(entity);
    }
    else
    {
        colliderProjectile.addComponent<ProjectileCollider>(entity);
        colliderProjectile.addComponent<PlayerProjectileCollider>(entity);
    }
}

void Weapon::shootProjectile(const sf::Time& dt, entt::entity entity,
                             WeaponComponent& weaponComponent, sf::Vector2f& weaponPosition,
                             sf::Vector2f& aimTarget)
{
    if (weaponComponent.clock.getElapsedTime().asMilliseconds() > mWeaponDelay)
    {
        adjustWeaponRotation(weaponComponent, weaponPosition, aimTarget);
        setupProjectile(dt, entity, weaponPosition);
        weaponComponent.clock.restart();
    }
}
