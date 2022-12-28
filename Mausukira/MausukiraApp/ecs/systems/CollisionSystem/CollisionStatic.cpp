#include "CollisionStatic.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "dungeon/map/MapUtils.h"
#include "dungeon/map/MapContext.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/ShootingComponents.h"

CollisionStatic::CollisionStatic(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
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
    for (auto entity: view)
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
    auto view2 = mRegistry.view<AttachmentPoint, ColliderComponent, ProjectileCollider>();
    for (auto entity: view2)
    {
        auto [attachmentPoint, collider, projectile] = view2.get(entity);
        auto parent = attachmentPoint.parent;

        auto& position = mRegistry.get<PositionComponent>(parent).mPosition;
        auto& velocity = mRegistry.get<VelocityComponent>(parent).mVelocity;
        auto futurePositionToCheck = position + velocity * dt.asSeconds();
        collider.mRectangle.setPosition(futurePositionToCheck);

        if (checkIfIntersects(collider, futurePositionToCheck))
        {
            mRegistry.destroy(parent);
            mRegistry.destroy(entity);
        }
    }
}
