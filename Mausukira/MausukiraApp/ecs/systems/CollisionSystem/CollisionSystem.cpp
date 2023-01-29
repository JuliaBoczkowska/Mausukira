#include "CollisionSystem.h"
#include "dungeon/map/MapUtils.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"

CollisionSystem::CollisionSystem(entt::registry& registry, MapContext& mapContext,
                                 SpatialHash& spatialGrid)
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
    updateSpatialGrid();
    mCollisionStatic.update(dt);
    mCollisionKinematic.update(dt);
}

void CollisionSystem::updateSpatialGrid()
{
    mRegistry.view<ColliderComponent>().each(
        [&](ColliderComponent& colliderComponent)
        {
            if (CollisionBox::CollisionType::PROJECTILE == colliderComponent.mCollisionType ||
                CollisionBox::CollisionType::ENEMY == colliderComponent.mCollisionType ||
                CollisionBox::CollisionType::HERO == colliderComponent.mCollisionType)
            {
                mSpatialGrid.update(colliderComponent);
            }
        });
}

void CollisionSystem::postUpdate()
{
    handleEntitiesRemovalAfterCollision();
}

void CollisionSystem::handleEntitiesRemovalAfterCollision()
{
    removeProjectileFromMap();
    removeEnemyFromMap();
    mSpatialGrid.clearSpatialGridMap();
}

void CollisionSystem::removeProjectileFromMap()
{
    mRegistry.view<ColliderComponent, AttachmentPoint, ProjectileCollider>().each(
        [&](auto entity, ColliderComponent& colliderComponent, AttachmentPoint& attachmentPoint,
            ProjectileCollider& projectileComponent)
        {
            if (colliderComponent.isHit)
            {
                auto parent = attachmentPoint.parent;

                mRegistry.destroy(parent);
                mRegistry.destroy(entity);
            }
        });
}

void CollisionSystem::removeEnemyFromMap()
{
    auto view = mRegistry.view<Relationship, EntityState, HealthComponent, EntityStatistic>();
    for (auto& entity: view)
    {
        auto [relationship, entityState, health, entityStatistic] = view.get(entity);
        auto& comp = mRegistry.get<Relationship>(entity);
        auto curr = comp.first_child;

        if (entityState.state == MobState::Died)
        {
            mRegistry.view<WeaponEnemy, AttachmentPoint>().each(
                [&](auto weaponEntity, WeaponEnemy& weaponEnemy, AttachmentPoint& attachmentPoint)
                {
                    auto parent = attachmentPoint.parent;
                    if (parent == entity)
                    {
                        mRegistry.destroy(weaponEntity);
                    }
                });
            mRegistry.destroy(entity);
            while (curr != entt::null)
            {
                auto toDestroy = curr;
                curr = mRegistry.get<Relationship>(curr).next;
                mRegistry.destroy(toDestroy);
            }
        }
    }
}
