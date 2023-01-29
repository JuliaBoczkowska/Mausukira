#ifndef WEAPON_H
#define WEAPON_H
#include "SFML/Window/Keyboard.hpp"
#include "ecs/components/ShootingComponents.h"
#include "entt/entity/registry.hpp"

class Entity;
class PositionComponent;
class Weapon
{
public:
    Weapon(entt::registry& registry, sf::RenderWindow& window);

    void setWeaponRotation(const sf::Vector2f& aimDirection,
                           WeaponComponent& weaponComponent) const;
    void adjustWeaponRotation(WeaponComponent& weaponComponent, sf::Vector2f& weaponPosition,
                              sf::Vector2f& aimTarget);

    virtual void shootProjectile(const sf::Time& dt, entt::entity entity,
                                 WeaponComponent& weaponComponent, sf::Vector2f& weaponPosition,
                                 sf::Vector2f& aimTarget);

    virtual void setupProjectile(const sf::Time& dt, entt::entity entity,
                                 sf::Vector2f& weaponPosition);

    virtual void setupProjectileCollider(Entity& projectile, entt::entity entity);

protected:
    entt::registry& mRegistry;
    sf::Vector2f mAimDirectionNormalized;

    /** Default weapon features */
    float mAttackSpeed{};
    float mWeaponDelay{};
    float mWeaponDamage{};
    int mProjectileSize{};
    sf::Color mProjectileColor{};
    friend class ProjectileShootSystem;
};


#endif// WEAPON_H
