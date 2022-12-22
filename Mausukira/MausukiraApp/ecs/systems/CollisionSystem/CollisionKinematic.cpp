#include "CollisionKinematic.h"

CollisionKinematic::CollisionKinematic(entt::registry& registry)
    : System(registry)
{

}

void CollisionKinematic::update(const sf::Time& dt)
{
    System::update(dt);
}
