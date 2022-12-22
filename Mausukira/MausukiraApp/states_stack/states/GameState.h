#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "dungeon/map/Map.h"
#include "states_stack/SharedContext.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "State.h"

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
    MapContext mMapContext;
    Scene mScene;
    Map mMap;
};

#endif// GAMESTATE_H
