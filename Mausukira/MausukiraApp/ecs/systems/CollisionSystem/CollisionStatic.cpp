#include "CollisionStatic.h"
#include "dungeon/map/MapContext.h"
#include "dungeon/map/MapUtils.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/DoorBodyComponent.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/entities/enemy/Enemy.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"

CollisionStatic::CollisionStatic(entt::registry& registry, MapContext& mapContext,
                                 SpatialHash& spatialGrid)
    : System(registry)
    , mMapContext(mapContext)
    , mSpatialGrid(spatialGrid)
{
}

void CollisionStatic::update(const sf::Time& dt)
{
    playerAndWallCollision(dt);
    playerAndDoorCollision();
    whenEnemyTouchesPlayerCollision(dt);
    bulletAndWallCollision(dt);
}

void CollisionStatic::playerAndDoorCollision()
{
    auto view = mRegistry.view<DoorBodyComponent>();
    for (auto& entity: view)
    {

        auto [doorBody] = view.get(entity);
        if (isColliderAndRectShapeColliding(*mPlayerFootCollider, doorBody.doorShape))
        {
            doorBody.changeLevel = true;
        }
    }
}

void CollisionStatic::playerAndWallCollision(const sf::Time& dt)
{
    auto view = mRegistry.view<PlayerComponent>();
    for (auto& entity: view)
    {
        auto& position = mRegistry.get<PositionComponent>(entity).mPosition;
        auto& velocity = mRegistry.get<VelocityComponent>(entity).mVelocity;
        auto* comp = mRegistry.try_get<Relationship>(entity);
        auto curr = comp->first_child;

        while (curr != entt::null)
        {
            auto& collider = mRegistry.get<ColliderComponent>(curr);
            if (collider.mCollisionType == CollisionBox::CollisionType::HERO)
            {
                mPlayerBodyCollider = &collider;
            }
            if (collider.mCollisionType == CollisionBox::CollisionType::FOOT)
            {
                mPlayerFootCollider = &collider;
                auto futurePositionToCheck = position + velocity * dt.asSeconds();

                collider.mRectangle.setPosition(futurePositionToCheck);
                auto prev = mRegistry.get<Relationship>(curr).prev;
                auto& bodyCollider = mRegistry.get<ColliderComponent>(prev);
                bodyCollider.mRectangle.setPosition(futurePositionToCheck);

                if (checkIfIntersects(collider, futurePositionToCheck))
                {
                    velocity = sf::Vector2f{0.f, 0.f};
                }
            }
            curr = mRegistry.get<Relationship>(curr).next;
        }
    }
}

bool CollisionStatic::checkIfIntersects(ColliderComponent& colliderComponent,
                                        const sf::Vector2f& futurePositionToCheck) const
{
    auto colliders =
        map_utils::getSurroundingTileCollisionBoxes(futurePositionToCheck, mMapContext.mTileMap);
    for (auto& collider: colliders)
    {
        sf::FloatRect colliderRect{collider->getGlobalBounds()};
        sf::FloatRect colliderComponentRect{colliderComponent.mRectangle.getGlobalBounds()};
        if (colliderRect.intersects(colliderComponentRect))
        {
            return true;
        }
    }
    return false;
}

void CollisionStatic::bulletAndWallCollision(const sf::Time& dt)
{
    mRegistry.view<AttachmentPoint, ColliderComponent, ProjectileCollider>().each(
        [&](auto entity, AttachmentPoint& attachmentPoint, ColliderComponent& colliderComponent,
            ProjectileCollider& projectile)
        {
            auto& parent = attachmentPoint.parent;

            auto position = mRegistry.get<PositionComponent>(parent).mPosition;
            auto velocity = mRegistry.get<ProjectileVelocityComponent>(parent).mVelocity;
            const auto& futurePositionToCheck = position + velocity;
            colliderComponent.mRectangle.setPosition(futurePositionToCheck);

            auto colliders = map_utils::getSurroundingTileCollisionBoxes(futurePositionToCheck,
                                                                         mMapContext.mTileMap);
            for (auto& collider: colliders)
            {
                if (isColliderAndRectShapeColliding(colliderComponent, *collider))
                {
                    colliderComponent.isHit = true;
                }
            }
        });
}

bool CollisionStatic::isColliderAndRectShapeColliding(ColliderComponent& colliderComponent,
                                                      sf::RectangleShape& collider)
{
    sf::FloatRect colliderRect{collider.getGlobalBounds()};
    sf::FloatRect colliderComponentRect{colliderComponent.mRectangle.getGlobalBounds()};
    return (colliderRect.intersects(colliderComponentRect) ||
            isBulletOutOfBounds(colliderComponent));
}

bool CollisionStatic::isBulletOutOfBounds(const ColliderComponent& colliderComponent)
{
    return colliderComponent.mRectangle.getPosition().x < 0 ||
           colliderComponent.mRectangle.getPosition().x > (MAP_SIZE_X * 31) ||
           colliderComponent.mRectangle.getPosition().y < 0 ||
           colliderComponent.mRectangle.getPosition().y > (MAP_SIZE_Y * 31);
}

void CollisionStatic::whenEnemyTouchesPlayerCollision(const sf::Time& time)
{
    updateEnemyCollider();
    auto view = mRegistry.view<AttachmentPoint, EnemyCollider, ColliderComponent>();
    for (auto& entity: view)
    {
        auto [attachmentPoint, enemyCollider, colliderComponent] = view.get(entity);
        auto& parent = attachmentPoint.parent;
        auto& enemyDamageComponent = mRegistry.get<EnemyDamage>(parent);
        auto& entityStats = mRegistry.get<EntityStatistic>(parent);
        if (isColliderAndRectShapeColliding(*mPlayerBodyCollider, colliderComponent.mRectangle))
        {
            if (enemyDamageComponent.clock.getElapsedTime().asSeconds() >
                enemyDamageComponent.mAttackSpeed)
            {
                mPlayerBodyCollider->isHit = true;
                mPlayerBodyCollider->damageTaken = enemyDamageComponent.mAttackDamage;
                enemyDamageComponent.clock.restart();
            }
        }
    }
}

void CollisionStatic::updateEnemyCollider()
{
    mRegistry.view<ColliderComponent, EnemyCollider, AttachmentPoint>().each(
        [&](ColliderComponent& colliderComponent, EnemyCollider& enemyCollider,
            AttachmentPoint& attachmentPoint)
        {
            auto& parent = attachmentPoint.parent;

            auto& position = mRegistry.get<PositionComponent>(parent).mPosition;
            colliderComponent.mRectangle.setPosition(position);
        });
}
