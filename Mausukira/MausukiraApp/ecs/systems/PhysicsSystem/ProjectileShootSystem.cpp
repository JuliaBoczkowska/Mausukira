#include "ProjectileShootSystem.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/entities/Entity.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/ColliderComponent.h"
#include "poly2tri/common/utils.h"

ProjectileShootSystem::ProjectileShootSystem(entt::registry& registry, SharedContext& sharedContext)
    : System(registry)
    , mRenderWindow(sharedContext.window())
{

}

void ProjectileShootSystem::update(const sf::Time& dt)
{
    sf::Vector2f aimDirection{ 0.f, 0.f };
    float rotAngle{ 0 };

    mRegistry.view<WeaponComponent, PositionComponent>().each(
        [&](WeaponComponent& weaponComponent, auto& positionComponent)
        {
            calculateDirectionalVector(positionComponent, aimDirection);
            normalizeDirectionalVector(aimDirection);
            setWeaponRotation(aimDirection, rotAngle, weaponComponent);
        });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        mRegistry.view<WeaponComponent>().each(
            [&](WeaponComponent& weaponComponent)
            {
                if (weaponComponent.clock.getElapsedTime().asMilliseconds() > 200)
                {
                    shootProjectile(dt);
                    weaponComponent.clock.restart();
                }
            });
    }
}

void ProjectileShootSystem::calculateDirectionalVector(const auto& positionComponent, sf::Vector2f& aimDirection)
{
    mWeaponCenter = positionComponent.mPosition;
    mMouseCoordinates = mRenderWindow.mapPixelToCoords((sf::Mouse::getPosition(mRenderWindow)));
    aimDirection = mMouseCoordinates - mWeaponCenter;
}

void ProjectileShootSystem::setWeaponRotation(const sf::Vector2f& aimDirection, float rotAngle,
    WeaponComponent& weaponComponent) const
{
    rotAngle = atan2(aimDirection.x, aimDirection.y) * (180 / M_PI);
    weaponComponent.mWeapon.setRotation(180 - rotAngle);
}

void ProjectileShootSystem::normalizeDirectionalVector(sf::Vector2f aimDirection)
{
    mAimDirectionNormalized = aimDirection / calculateVectorLength(aimDirection);
}

float ProjectileShootSystem::calculateVectorLength(sf::Vector2f aimDirection) const
{
    return static_cast<float>(sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2)));
}

void ProjectileShootSystem::shootProjectile(const sf::Time& dt)
{
    mRegistry.view<WeaponComponent>().each(
        [&](auto weaponEntity, WeaponComponent& weapon)
        {
            setupProjectile(dt, weaponEntity);
        });
}

void ProjectileShootSystem::setupProjectile(const sf::Time& dt, auto weaponEntity)
{
    Entity projectile{ mRegistry.create(), &mRegistry };
    projectile.addComponent<PositionComponent>(
        mRegistry.get<PositionComponent>(weaponEntity).mPosition);
    projectile.addComponent<VelocityComponent>(mAimDirectionNormalized * 7000.f * dt.asSeconds());
    projectile.addComponent<ProjectileBody>();

    setupProjectileCollider(projectile);
}

void ProjectileShootSystem::setupProjectileCollider(Entity& projectile)
{
    Entity colliderProjectile{ mRegistry.create(), &mRegistry };
    sf::RectangleShape rect(CollisionBox::setupCollider(
        projectile.getComponent<ProjectileBody>().mProjectile.getGlobalBounds(),
        CollisionBox::CollisionType::BODY));
    colliderProjectile.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::BODY);
    colliderProjectile.addComponent<AttachmentPoint>(projectile.getEntity());
    colliderProjectile.addComponent<ProjectileCollider>();
}
