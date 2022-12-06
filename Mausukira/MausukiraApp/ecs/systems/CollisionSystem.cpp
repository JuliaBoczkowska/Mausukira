#include "CollisionSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/TransformComponent.h"
#include "scene/map/MapUtils.h"

CollisionSystem::CollisionSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{
}

void CollisionSystem::handleInput(sf::Event& event)
{
}

void CollisionSystem::update(const sf::Time& dt)
{

    mRegistry.view<ColliderComponent, TransformComponent>().each(
        [&](ColliderComponent& colliderComponent, TransformComponent& transformComponent)
        {
            auto colliders = map_utils::getSurroundingCollisionBoxes(transformComponent.position(),
                                                                     mMapContext.mTileMap);
            colliderComponent.mIsColliding = false;
            for (auto& collider: colliders)
            {
                if (collider->intersects(colliderComponent.mCollisionBox))
                {
                    colliderComponent.mIsColliding = true;
                }
            }
            // = isColliding;
        });
}
