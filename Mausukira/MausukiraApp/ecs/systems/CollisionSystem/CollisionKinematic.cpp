#include "CollisionKinematic.h"
#include "dungeon/map/MapUtils.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/systems/SpatialHashing/SpatialHash.h"


CollisionKinematic::CollisionKinematic(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid)
    : System(registry)
    , mMapContext(mapContext)
    , mSpatialGrid(spatialGrid)
{
}

void CollisionKinematic::update(const sf::Time& dt)
{
    mRegistry.view<AttachmentPoint, ColliderComponent>().each(
        [&](AttachmentPoint& attachmentPoint, ColliderComponent& colliderComponent)
        {
            mSpatialGrid.update(colliderComponent);
        });
    projectileAndEnemyCollision();
}

void CollisionKinematic::projectileAndEnemyCollision()
{
    auto view = mRegistry.view<ColliderComponent, ProjectileCollider>();
    for (auto& entity: view)
    {
        auto [colliderComponent, projectile] = view.get(entity);

        auto colliders = mSpatialGrid.getCollidersInTheSameCell(colliderComponent);

        for (auto& collider: colliders)
        {
            if (isColliderIntersectingEnemy(colliderComponent, collider))
            {
                colliderComponent.isHit = true;

            }
        }
    }
}

bool
CollisionKinematic::isColliderIntersectingEnemy(ColliderComponent& colliderComponent, ColliderComponent* collider) const
{
    sf::FloatRect colliderRect{ collider->mRectangle.getGlobalBounds() };
    sf::FloatRect colliderComponentRect{ colliderComponent.mRectangle.getGlobalBounds() };
    if (!(CollisionBox::CollisionType::ENEMY == collider->mCollisionType))
    {
        return false;
    }
    return colliderRect.intersects(colliderComponentRect);

}
