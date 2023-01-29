#ifndef PROJECTILESHOOTSYSTEM_H
#define PROJECTILESHOOTSYSTEM_H

#include "ecs/components/ShootingComponents.h"
#include "ecs/systems/PhysicsSystem/weapon/Weapon.h"
#include "ecs/systems/System.h"
#include "states_stack/SharedContext.h"

class SpatialHash;

class Entity;

class ProjectileShootSystem : public System
{
    using WeaponFactory =
        std::unordered_map<WeaponType, std::function<std::unique_ptr<Weapon>(void)>>;

public:
    ProjectileShootSystem(entt::registry& registry, SharedContext& sharedContext,
                          SpatialHash& spatialGrid);

    template<class Weapon>
    void registerWeapon(const WeaponType& type)
    {
        mWeaponFactory[type] = [this]() -> std::unique_ptr<Weapon>
        {
            return std::make_unique<Weapon>(mRegistry, mRenderWindow);
        };
    }
    void update(const sf::Time& dt) override;

private:
    void checkIfChangeWeaponTriggered(const WeaponType& type);

private:
    sf::RenderWindow& mRenderWindow;
    std::unordered_map<entt::entity, std::unique_ptr<Weapon>> mWeapon;
    WeaponFactory mWeaponFactory;
    void playerShoot(const sf::Time& dt);
    void enemyShoot(const sf::Time& dt);
};

#endif// PROJECTILESHOOTSYSTEM_H
