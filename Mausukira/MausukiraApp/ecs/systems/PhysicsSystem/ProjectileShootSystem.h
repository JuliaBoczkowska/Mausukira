#ifndef PROJECTILESHOOTSYSTEM_H
#define PROJECTILESHOOTSYSTEM_H

#include "ecs/systems/System.h"
#include "states_stack/SharedContext.h"
#include "ecs/components/ShootingComponents.h"

class SpatialHash;

class ProjectileShootSystem : public System
{
public:
    ProjectileShootSystem(entt::registry& registry, SharedContext& sharedContext, SpatialHash& spatialGrid);

    void update(const sf::Time& dt) override;

private:
    void calculateDirectionalVector(const auto& positionComponent, sf::Vector2f& aimDirection);

    void normalizeDirectionalVector(sf::Vector2f aimDirection);

    float calculateVectorLength(sf::Vector2f aimDirection) const;

    void setupProjectileCollider(Entity& projectile);

    void setWeaponRotation(const sf::Vector2f& aimDirection, float rotAngle, WeaponComponent& weaponComponent) const;

    void shootProjectile(const sf::Time& dt);

    void setupProjectile(const sf::Time& dt, auto weaponEntity);

private:
    sf::Vector2f mMouseCoordinates{};
    sf::Vector2f mAimDirectionNormalized{};
    sf::Vector2f mWeaponCenter{};
    sf::RenderWindow& mRenderWindow;
    SpatialHash& mSpatialGrid;
};

#endif //PROJECTILESHOOTSYSTEM_H
