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

bool CollisionSystem::checkIfAllowsToUpdatePosition(ColliderComponent& colliderComponent,
                                                    const sf::Vector2f& futurePositionToCheck) const
{
    auto colliders =
        map_utils::getSurroundingCollisionBoxes(futurePositionToCheck, mMapContext.mTileMap);
    for (auto& collider: colliders)
    {
        if (collider->isColliding(colliderComponent.mCollisionBox))
        {
            return true;
        }
    }
    return false;
}


void CollisionSystem::update(const sf::Time& dt)
{
    mRegistry.view<ColliderComponent, TransformComponent>().each(
        [&](ColliderComponent& colliderComponent, TransformComponent& transformComponent)
        {
            auto futurePositionToCheck =
                transformComponent() + transformComponent.mVelocity * dt.asSeconds();
            transformComponent.mColliderComponent.setPosition(futurePositionToCheck);
            if (checkIfAllowsToUpdatePosition(colliderComponent, futurePositionToCheck))
            {
                transformComponent.mVelocity = sf::Vector2f{0.f, 0.f};
            }
        });
}
void CollisionSystem::draw(sf::RenderWindow& window)
{
}
