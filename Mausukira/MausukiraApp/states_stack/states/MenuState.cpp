#include "MenuState.h"
#include "states_stack/StateHandler.h"
#include <TGUI/TGUI.hpp>


MenuState::MenuState(StateHandler& stateManager, StateType type, sf::View view)
    : State(stateManager, type, view)
    , gui(context().window())
{
    setupBackground();
    setupStartButton();
    setupQuitButton();
    setupText();
}

void MenuState::setupText()
{
    auto size = context().window().getSize();
    mGameTitle.setColor(sf::Color::White);
    mGameTitle.setCharacterSize(30);
    font.loadFromFile("resources/arial.ttf");
    mGameTitle.setFont(font);
    mGameTitle.setString({"Roguelike game"});
    mGameTitle.setOrigin(
        mGameTitle.getLocalBounds().left + mGameTitle.getLocalBounds().width / 2.0f,
        mGameTitle.getLocalBounds().top + mGameTitle.getLocalBounds().height / 2.0f);
    mGameTitle.setPosition(size.x / 2.0f, 300);
}

void MenuState::setupQuitButton()
{
    auto quit = tgui::Button::create("Quit");
    quit->setSize({"40%", "10%"});
    quit->setPosition({"30%", "60%"});
    quit->onPress(
        [this]()
        {
            context().window().close();
        });
    gui.add(quit);
}

void MenuState::setupStartButton()
{
    auto start = tgui::Button::create("New Game");
    start->setSize({"40%", "10%"});
    start->setPosition({"30%", "40%"});
    start->onPress(
        [this]()
        {
            mStateHandler.switchTo(StateType::GAME_STATE);
            mStateHandler.removeState(mStateType);
        });
    gui.add(start);
}

void MenuState::setupBackground()
{
    auto picture = tgui::Picture::create("resources/tiles/background.png");
    picture->setSize({"100%", "100%"});
    gui.add(picture);
}

void MenuState::handleInput(sf::Event& event)
{
    gui.handleEvent(event);
}

void MenuState::update(const sf::Time& dt)
{
}

void MenuState::draw()
{
    gui.draw();
    context().window().draw(mGameTitle);
}
