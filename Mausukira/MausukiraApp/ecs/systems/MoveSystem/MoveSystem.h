#ifndef MOVESYSTEM_H
#define MOVESYSTEM_H

#include "ecs/systems/System.h"
#include "PlayerMoveSystem.h"

class MoveSystem : public System
{
public:
    explicit MoveSystem(entt::registry& registry);

    void handleInput(sf::Event& event) override;

    void update(const sf::Time& dt) override;

    void postUpdate() override;

private:
    PlayerMoveSystem mPlayerMoveSystem;
};


#endif //MOVESYSTEM_H
