#include "MenuState.h"
#include "../../gui/Button.h"
#include "../StateHandler.h"
#include <TGUI/TGUI.hpp>
#include <iostream>

MenuState::MenuState(StateHandler& stateManager, StateType type, sf::View view)
    : State(stateManager, type, view)
{
}

void MenuState::handleInput(sf::Event& event)
{
}

void MenuState::update(const sf::Time& dt)
{
}

void MenuState::draw()
{
}
