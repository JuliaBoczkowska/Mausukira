#ifndef STATE_H
#define STATE_H

#include "SFML/Graphics/View.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include <memory>

class StateHandler;

enum class StateType
{
    INTRO_STATE,
    MENU_STATE,
    GAME_STATE,
    GAME_OVER_STATE,
    PAUSE_STATE
};

class State
{
public:
    explicit State(StateHandler& stateHandler, StateType type, sf::View view);

    virtual ~State() = default;

    sf::View& GetView()
    {
        return mView;
    }

    virtual void handleInput(sf::Event& event) = 0;

    virtual void update(const sf::Time& dt) = 0;

    virtual void draw() = 0;

protected:
    StateHandler& mStateHandler;
    StateType mStateType;
    sf::View mView;
};

#endif// STATE_H
