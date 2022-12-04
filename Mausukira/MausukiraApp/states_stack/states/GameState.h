#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../scene/map/Map.h"
#include "../SharedContext.h"
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

    entt::registry registry;
    MapContext mMapContext;
    Scene mScene;
    Map mMap;
};

#endif// GAMESTATE_H
