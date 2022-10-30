#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../SharedContext.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "State.h"

class GameState : public State
{
public:
    GameState(StateHandler& stateManager, StateType type);
    ~GameState() = default;

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw() override;

    SharedContext& mContext;
    sf::RectangleShape rect;
};

#endif//GAMESTATE_H
