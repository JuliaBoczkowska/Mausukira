#include "ProjectileShootSystem.h"
#include "Window.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/entities/Entity.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"
#include "ecs/systems/PhysicsSystem/weapon/MachineGun.h"
#include "ecs/systems/PhysicsSystem/weapon/Pistol.h"
#include "ecs/systems/PhysicsSystem/weapon/Shotgun.h"

ProjectileShootSystem::ProjectileShootSystem(entt::registry& registry, SharedContext& sharedContext,
                                             SpatialHash& spatialGrid)
    : System(registry)
    , mRenderWindow(sharedContext.window())
{
    registerWeapon<Shotgun>(WeaponType::SHOTGUN);
    registerWeapon<MachineGun>(WeaponType::MACHINE_GUN);
    registerWeapon<Pistol>(WeaponType::PISTOL);

    mRegistry.view<WeaponComponent, AttachmentPoint>().each(
        [&](auto entity, WeaponComponent& weaponComponent, AttachmentPoint& attachmentPoint)
        {
            mWeapon.emplace(attachmentPoint.parent,
                            mWeaponFactory.find(weaponComponent.type)->second());
        });
}

void ProjectileShootSystem::update(const sf::Time& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
    {
        checkIfChangeWeaponTriggered(WeaponType::MACHINE_GUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
    {
        checkIfChangeWeaponTriggered(WeaponType::SHOTGUN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
    {
        checkIfChangeWeaponTriggered(WeaponType::PISTOL);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        playerShoot(dt);
    }
    enemyShoot(dt);
}

void ProjectileShootSystem::enemyShoot(const sf::Time& dt)
{
    mRegistry.view<WeaponComponent, WeaponEnemy, AttachmentPoint>().each(
        [&](auto entity, WeaponComponent& weaponComponent, WeaponEnemy& weaponPlayer,
            AttachmentPoint& attachmentPoint)
        {
            auto aiComponent = mRegistry.get<AiComponent>(attachmentPoint.parent);
            auto sensorComponent = mRegistry.get<SensorComponent>(attachmentPoint.parent);
            auto& enemyDamageComponent = mRegistry.get<EnemyDamage>(attachmentPoint.parent);
            auto weaponPosition = mRegistry.get<PositionComponent>(entity);
            EntityStatistic entityStats = mRegistry.get<EntityStatistic>(attachmentPoint.parent);

            auto playerPos = aiComponent.mPlayerPositionComponent;
            auto time = enemyDamageComponent.shootingClock.getElapsedTime().asMilliseconds();
            if (time - enemyDamageComponent.mTimeProjectileShot > entityStats.mAttackSpeed)
            {
                if (sensorComponent.mIsPlayerInFieldOfView)
                {
                    mWeapon.find(attachmentPoint.parent)
                        ->second->shootProjectile(dt, entity, weaponComponent,
                                                  weaponPosition.mPosition, playerPos->mPosition);
                    enemyDamageComponent.mTimeProjectileShot =
                        enemyDamageComponent.shootingClock.getElapsedTime().asMilliseconds();
                }
            }
        });
}

void ProjectileShootSystem::playerShoot(const sf::Time& dt)
{
    mRegistry.view<WeaponComponent, WeaponPlayer, AttachmentPoint>().each(
        [&](auto entity, WeaponComponent& weaponComponent, WeaponPlayer& weaponPlayer,
            AttachmentPoint& attachmentPoint)
        {
            auto weaponPosition = mRegistry.template get<PositionComponent>(entity).mPosition;
            auto mouseCoordinates =
                mRenderWindow.mapPixelToCoords((sf::Mouse::getPosition(mRenderWindow)));
            mWeapon.find(attachmentPoint.parent)
                ->second->shootProjectile(dt, entity, weaponComponent, weaponPosition,
                                          mouseCoordinates);
        });
}

void ProjectileShootSystem::checkIfChangeWeaponTriggered(const WeaponType& type)
{
    mRegistry.view<WeaponComponent, AttachmentPoint, WeaponPlayer>().each(
        [&](auto entity, WeaponComponent& weaponComponent, AttachmentPoint& attachmentPoint,
            WeaponPlayer)
        {
            mWeapon.find(attachmentPoint.parent)->second =
                std::unique_ptr<Weapon>(mWeaponFactory.find(type)->second());
        });
}