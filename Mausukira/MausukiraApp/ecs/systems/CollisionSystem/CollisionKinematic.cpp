#include "CollisionKinematic.h"
#include "dungeon/map/MapUtils.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"
#include "ecs/components/AttachmentPoint.h"


CollisionKinematic::CollisionKinematic(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid)
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
    auto view = mRegistry.view<ColliderComponent, AttachmentPoint, ProjectileCollider>();
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
