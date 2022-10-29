#include "MenuState.h"
#include <iostream>
#include "../../gui/Button.h"

MenuState::MenuState(std::unique_ptr<StateHandler> stateManager, StateType type)
    : State(std::move(stateManager), type)
{
    std::shared_ptr<Button> startGame;
    startGame->setText("BUTTON");
    startGame->setCallback([](){ std::cout << "uwu" << std::endl; });
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
