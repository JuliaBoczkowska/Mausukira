#include "CollisionSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "dungeon/map/MapUtils.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/systems/SpatialHashing/SpatialHash.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/AttackType.h"

CollisionSystem::CollisionSystem(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid)
    : System(registry)
    , mMapContext(mapContext)
    , mSpatialGrid(spatialGrid)
    , mCollisionKinematic(registry, mapContext, spatialGrid)
    , mCollisionStatic(registry, mapContext, spatialGrid)
{
    auto view = mRegistry.view<AttachmentPoint, ColliderComponent>();
    for (auto entity: view)
    {
        auto [attachmentPoint, colliderC] = view.get(entity);
        auto parent = attachmentPoint.parent;

        auto& position = mRegistry.get<PositionComponent>(parent).mPosition;

        colliderC.mRectangle.setPosition(position);
    }
//
//    mRegistry.view<ColliderComponent>().each(
//        [&](ColliderComponent& colliderComponent)
//        {
//            if (colliderComponent.mCollisionType == CollisionBox::CollisionType::ENEMY)
//            {
//                mSpatialGrid.addColliders(colliderComponent);
//            }
//        });
}


void CollisionSystem::update(const sf::Time& dt)
{
    mRegistry.view<AttachmentPoint, ColliderComponent>().each(
        [&](AttachmentPoint& attachmentPoint, ColliderComponent& colliderComponent)
        {
            if (CollisionBox::CollisionType::PROJECTILE == colliderComponent.mCollisionType ||
                CollisionBox::CollisionType::ENEMY == colliderComponent.mCollisionType)
            {
                mSpatialGrid.update(colliderComponent);
            }
        });
    mCollisionStatic.update(dt);
    mCollisionKinematic.update(dt);
}

void CollisionSystem::postUpdate()
{
    mRegistry.view<ColliderComponent, AttachmentPoint>().each(
        [&](auto entity, ColliderComponent& colliderComponent,
            AttachmentPoint& attachmentPoint)
        {
            if (colliderComponent.isHit)
            {
                auto parent = attachmentPoint.parent;

                mRegistry.destroy(parent);
                mRegistry.destroy(entity);
            }

        });
    mSpatialGrid.clearSpatialGridMap();
}
