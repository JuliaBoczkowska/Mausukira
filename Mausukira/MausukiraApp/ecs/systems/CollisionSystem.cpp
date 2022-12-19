#include "CollisionSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/weapon/Weapon.h"
#include "scene/map/MapUtils.h"

CollisionSystem::CollisionSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{
}

void CollisionSystem::handleInput(sf::Event& event)
{
}

bool CollisionSystem::checkIfAllowsToUpdatePosition(ColliderComponent& colliderComponent,
                                                    const sf::Vector2f& futurePositionToCheck) const
{
    auto colliders =
        map_utils::getSurroundingCollisionBoxes(futurePositionToCheck, mMapContext.mTileMap);
    for (auto& collider: colliders)
    {
        if (collider->isColliding(colliderComponent.mCollisionBox))
        {
            return true;
        }
    }
    return false;
}


void CollisionSystem::update(const sf::Time& dt)
{
    playerAndWallCollision(dt);

    std::vector<CollisionBox*> projectileCollisionBoxes;
    projectileAndWall(projectileCollisionBoxes);
    enemyAndProjectileCollision(projectileCollisionBoxes);
    eraseProjectilesThatCollide();
}

void CollisionSystem::projectileAndWall(std::vector<CollisionBox*>& projectileCollisionBoxes)
{
    mRegistry.view<Weapon>().each(
        [&](Weapon& weapon)
        {
            for (auto it = weapon.mProjectiles.begin(); it != weapon.mProjectiles.end(); it++)
            {
                auto projectile = *it;
                projectileCollisionBoxes.emplace_back(&projectile->CollisionBox);
                auto futurePositionToCheck =
                    projectile->mProjectile.getPosition() + projectile->mCurrVelocity;
                auto colliders = map_utils::getSurroundingCollisionBoxes(futurePositionToCheck,
                                                                         mMapContext.mTileMap);
                for (auto& collider: colliders)
                {
                    if (collider->isColliding(projectile->CollisionBox))
                    {
                        projectile->CollisionBox.mIsColliding = true;
                    }
                }
            }
        });
}

void CollisionSystem::enemyAndProjectileCollision(
    std::vector<CollisionBox*>& projectileCollisionBoxes)
{
    mRegistry.view<ColliderComponent, TransformComponent, EntityStatistic, HealthComponent>().each(
        [&](ColliderComponent& colliderComponent, TransformComponent& transformComponent,
            EntityStatistic& entityStatistic, HealthComponent& healthComponent)
        {
            for (auto& projectile: projectileCollisionBoxes)
            {
                if (projectile->isColliding(colliderComponent.mCollisionBox))
                {
                    projectile->mIsColliding = true;
                    healthComponent.damageHealth(5);
                }
            }
        });
}

void CollisionSystem::playerAndWallCollision(const sf::Time& dt)
{
    mRegistry.view<ColliderComponent, TransformComponent>().each(
        [&](ColliderComponent& colliderComponent, TransformComponent& transformComponent)
        {
            auto futurePositionToCheck =
                transformComponent() + transformComponent.mVelocity * dt.asSeconds();
            transformComponent.mColliderComponent.setPosition(futurePositionToCheck);
            if (checkIfAllowsToUpdatePosition(colliderComponent, futurePositionToCheck))
            {
                transformComponent.mVelocity = sf::Vector2f{0.f, 0.f};
            }
        });
}

void CollisionSystem::eraseProjectilesThatCollide()
{
    mRegistry.view<Weapon>().each(
        [&](Weapon& weapon)
        {
            auto it = weapon.mProjectiles.begin();
            while (it != weapon.mProjectiles.end())
            {
                if ((*it)->CollisionBox.mIsColliding)
                {
                    weapon.mProjectiles.erase(it++);
                }
                else
                {

                    ++it;
                }
            }
        });
}


void CollisionSystem::draw(sf::RenderWindow& window)
{
}
