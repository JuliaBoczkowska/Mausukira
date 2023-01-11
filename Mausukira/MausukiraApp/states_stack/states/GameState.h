#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "ecs/Scene.h"
#include "entt/entity/registry.hpp"

class Scene;

class GameState : public State
{
public:
    GameState(StateHandler& stateManager, StateType type, sf::View view);

    ~GameState() = default;

    void handleInput(sf::Event& event) override;

    void update(const sf::Time& dt) override;

    void draw() override;

private:
    void checkIfPauseState(const sf::Event& event);

private:
    entt::registry registry;
    Scene mScene;
    bool isPlayerDead{false};
};

#endif// GAMESTATE_H
