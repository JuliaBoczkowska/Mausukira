#include "CollisionKinematic.h"
#include "ecs/components/ColliderComponent.h"

#include "dungeon/map/MapUtils.h"

CollisionKinematic::CollisionKinematic(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{

}

void CollisionKinematic::update(const sf::Time& dt)
{
}