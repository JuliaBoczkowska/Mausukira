#include "CollisionSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "dungeon/map/MapUtils.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/ShootingComponents.h"

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
    mRegistry.view<ColliderComponent, AttachmentPoint, ProjectileCollider>().each(
        [&](auto entity, ColliderComponent& colliderComponent,
            AttachmentPoint& attachmentPoint, ProjectileCollider& projectileComponent)
        {
            if (colliderComponent.isHit)
            {
                auto parent = attachmentPoint.parent;

                mRegistry.destroy(parent);
                mRegistry.destroy(entity);
            }

        });

    auto view = mRegistry.view<Relationship, EntityState, HealthComponent, EntityStatistic>();
    for (auto& entity: view)
    {
        auto [relationship, entityState, health, entityStatistic] = view.get(entity);
        auto& comp = mRegistry.get<Relationship>(entity);
        auto curr = comp.first_child;

        if (entityState.state == MobState::Died)
        {
            mRegistry.destroy(entity);
            while (curr != entt::null)
            {
                auto toDestroy = curr;
                curr = mRegistry.get<Relationship>(curr).next;
                mRegistry.destroy(toDestroy);
            }
        }
    }
    mSpatialGrid.clearSpatialGridMap();
}
