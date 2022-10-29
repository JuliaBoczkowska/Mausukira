#include "IntroState.h"

IntroState::IntroState(std::unique_ptr<StateHandler> stateHandler, StateType type) : State(std::move(stateHandler), type)
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
