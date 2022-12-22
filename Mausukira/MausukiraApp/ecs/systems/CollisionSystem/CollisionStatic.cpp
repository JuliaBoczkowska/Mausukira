#include "CollisionStatic.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "dungeon/map/MapUtils.h"
#include "dungeon/map/MapContext.h"

CollisionStatic::CollisionStatic(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{

}

void CollisionStatic::update(const sf::Time& dt)
{
    playerAndWallCollision(dt);
}

void CollisionStatic::playerAndWallCollision(const sf::Time& dt)
{
    mRegistry.view<ColliderComponent, PositionComponent, VelocityComponent>().each(
        [&](ColliderComponent& colliderComponent, PositionComponent& positionComponent,
            VelocityComponent& velocityComponent)
        {
            auto futurePositionToCheck =
                positionComponent.mPosition + velocityComponent.mVelocity * dt.asSeconds();
            colliderComponent.mRectangle.setPosition(futurePositionToCheck);
            if (checkIfAllowsToUpdatePosition(colliderComponent, futurePositionToCheck))
            {
                velocityComponent.mVelocity = sf::Vector2f{ 0.f, 0.f };
            }
        });
}

bool CollisionStatic::checkIfAllowsToUpdatePosition(ColliderComponent& colliderComponent,
    const sf::Vector2f& futurePositionToCheck) const
{
    auto colliders =
        map_utils::getSurroundingCollisionBoxes(futurePositionToCheck, mMapContext.mTileMap);
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