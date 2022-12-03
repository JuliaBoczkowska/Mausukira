#include "MenuState.h"
#include "../../gui/Button.h"
#include "../StateHandler.h"
#include <iostream>

MenuState::MenuState(StateHandler& stateManager, StateType type, sf::View view)
    : State(stateManager, type, view)
{
    std::shared_ptr<Button> startGame;
    startGame->setText("BUTTON");
    startGame->setCallback(
        []()
        {
            std::cout << ":))" << std::endl;
        });
    mGuiComponents.addComponent(startGame);
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
