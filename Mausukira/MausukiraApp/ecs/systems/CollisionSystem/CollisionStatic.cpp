#include "CollisionStatic.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "dungeon/map/MapUtils.h"
#include "dungeon/map/MapContext.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"

CollisionStatic::CollisionStatic(entt::registry& registry, MapContext& mapContext, SpatialHash& spatialGrid)
    : System(registry)
    , mMapContext(mapContext)
    , mSpatialGrid(spatialGrid)
{

}

void CollisionStatic::update(const sf::Time& dt)
{
    playerAndWallCollision(dt);
    bulletAndWallCollision(dt);
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
            if (collider.mCollisionType == CollisionBox::CollisionType::FOOT)
            {
                auto futurePositionToCheck = position + velocity * dt.asSeconds();

                collider.mRectangle.setPosition(futurePositionToCheck);

                if (checkIfIntersects(collider, futurePositionToCheck))
                {
                    velocity = sf::Vector2f{ 0.f, 0.f };
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
        sf::FloatRect colliderRect{ collider->getGlobalBounds() };
        sf::FloatRect colliderComponentRect{ colliderComponent.mRectangle.getGlobalBounds() };
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

            auto& position = mRegistry.get<PositionComponent>(parent).mPosition;
            auto& velocity = mRegistry.get<VelocityComponent>(parent).mVelocity;
            const auto& futurePositionToCheck = position + velocity * dt.asSeconds();
            colliderComponent.mRectangle.setPosition(futurePositionToCheck);

            auto colliders =
                map_utils::getSurroundingTileCollisionBoxes(futurePositionToCheck, mMapContext.mTileMap);
            for (auto& collider: colliders)
            {
                if (isBulletCollidingWall(colliderComponent, collider))
                {
                    colliderComponent.isHit = true;
                }
            }
        });
}

bool CollisionStatic::isBulletCollidingWall(ColliderComponent& colliderComponent, sf::RectangleShape* const& collider)
{
    sf::FloatRect colliderRect{ collider->getGlobalBounds() };
    sf::FloatRect colliderComponentRect{ colliderComponent.mRectangle.getGlobalBounds() };
    return (colliderRect.intersects(colliderComponentRect) || isBulletOutOfBounds(colliderComponent));
}

bool CollisionStatic::isBulletOutOfBounds(const ColliderComponent& colliderComponent)
{
    return colliderComponent.mRectangle.getPosition().x<0 || colliderComponent.mRectangle.getPosition().x>(
        MAP_SIZE_X * 31) ||
           colliderComponent.mRectangle.getPosition().y<0 || colliderComponent.mRectangle.getPosition().y>(
               MAP_SIZE_Y * 31);
}
