#include "CollisionKinematic.h"
#include "dungeon/map/MapUtils.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"


CollisionKinematic::CollisionKinematic(entt::registry& registry, MapContext& mapContext,
                                       SpatialHash& spatialGrid)
    : System(registry)
    , mMapContext(mapContext)
    , mSpatialGrid(spatialGrid)
{
}

void CollisionKinematic::update(const sf::Time& dt)
{
    projectileAndEnemyCollision();
}

void CollisionKinematic::projectileAndEnemyCollision()
{
    auto view = mRegistry.view<ColliderComponent, AttachmentPoint, PlayerProjectileCollider>();
    for (auto& entity: view)
    {
        auto [colliderComponent, attachmentPoint, projectile] = view.get(entity);
        auto colliders = mSpatialGrid.getCollidersInTheSameCell(colliderComponent);

        for (auto& collider: colliders)
        {
            if (isColliderIntersectingEnemy(colliderComponent, collider))
            {
                colliderComponent.isHit = true;
                collider->isHit = true;
                break;
            }
        }
    }

    auto view2 = mRegistry.view<ColliderComponent, AttachmentPoint, EnemyProjectileCollider>();
    for (auto& entity: view2)
    {
        auto [projectileColliderComponent, attachmentPoint, projectileCollider] = view2.get(entity);
        auto colliders = mSpatialGrid.getCollidersInTheSameCell(projectileColliderComponent);
        auto projectile = mRegistry.get<ProjectileDamage>(attachmentPoint.parent);

        for (auto& collider: colliders)
        {
            if (isProjectileIntersectingHero(projectileColliderComponent, collider))
            {
                projectileColliderComponent.isHit = true;
                collider->damageTaken = projectile.mDamage;
                collider->isHit = true;
                break;
            }
        }
    }
}

bool CollisionKinematic::isColliderIntersectingEnemy(ColliderComponent& colliderComponent,
                                                     ColliderComponent* collider) const
{
    sf::FloatRect colliderRect{collider->mRectangle.getGlobalBounds()};
    sf::FloatRect colliderComponentRect{colliderComponent.mRectangle.getGlobalBounds()};
    if (!(CollisionBox::CollisionType::ENEMY == collider->mCollisionType))
    {
        return false;
    }
    return colliderRect.intersects(colliderComponentRect);
}

bool CollisionKinematic::isProjectileIntersectingHero(ColliderComponent& colliderComponent,
                                                      ColliderComponent* collider) const
{
    sf::FloatRect colliderRect{collider->mRectangle.getGlobalBounds()};
    sf::FloatRect colliderComponentRect{colliderComponent.mRectangle.getGlobalBounds()};
    if (!(CollisionBox::CollisionType::HERO == collider->mCollisionType))
    {
        return false;
    }
    return colliderRect.intersects(colliderComponentRect);
}
