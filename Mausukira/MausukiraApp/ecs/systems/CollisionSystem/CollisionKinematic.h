#ifndef COLLISIONKINEMATIC_H
#define COLLISIONKINEMATIC_H

#include "ecs/systems/System.h"

class CollisionKinematic : public System
{
public:
    explicit CollisionKinematic(entt::registry& registry);

    void update(const sf::Time& dt) override;
};


#endif //COLLISIONKINEMATIC_H
