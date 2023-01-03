#ifndef STATE_H
#define STATE_H

#include "SFML/Graphics/View.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include <memory>

class StateHandler;

class SharedContext;

enum class StateType
{
    MENU_STATE,
    GAME_STATE,
    GAME_OVER_STATE,
    PAUSE_STATE
};

class State
{
public:
    explicit State(StateHandler& stateHandler, StateType type, sf::View view,
        bool isTransparent = false);

    virtual ~State() = default;

    virtual void handleInput(sf::Event& event) = 0;

    virtual void update(const sf::Time& dt) = 0;

    virtual void draw() = 0;

    SharedContext& context();

    bool mIsTransparent;
    StateType mStateType;
    sf::View mView;

protected:
    StateHandler& mStateHandler;
};

#endif// STATE_H
