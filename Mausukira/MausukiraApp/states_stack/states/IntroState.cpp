#include "IntroState.h"
#include "../StateHandler.h"

IntroState::IntroState(StateHandler& stateHandler, StateType type)
    : State(stateHandler, type)
{
}

void IntroState::handleInput(sf::Event& event)
{
}

void IntroState::update(const sf::Time& dt)
{
}

void IntroState::draw()
{
}
