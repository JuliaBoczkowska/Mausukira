#include "GameOverState.h"
#include "Window.h"
#include "states_stack/SharedContext.h"
#include "states_stack/StateHandler.h"

GameOverState::GameOverState(StateHandler& stateManager, StateType type, sf::View view,
                             bool isTransparent)
    : State(stateManager, type, view, isTransparent)
    , gui(context().window())
{
    background.setSize(sf::Vector2f(context().window().getView().getSize()));
    background.setOrigin(
        background.getLocalBounds().left + background.getLocalBounds().width / 2.0f,
        background.getLocalBounds().top + background.getLocalBounds().height / 2.0f);
    background.setPosition(sf::Vector2f(context().window().getView().getCenter()));
    background.setFillColor(sf::Color(100, 0, 0, 100));
    setupText();
    setupPlayAgainButton();
    setupConntinueButton();
    setupMainMenuButton();
}

void GameOverState::handleInput(sf::Event& event)
{
    gui.handleEvent(event);
}

void GameOverState::update(const sf::Time& dt)
{
}

void GameOverState::draw()
{
    context().window().draw(background);
    context().window().setView(context().window().getDefaultView());
    gui.draw();
    context().window().draw(mTitle);
    context().window().setView(mView);
}

void GameOverState::setupPlayAgainButton()
{
    auto start = tgui::Button::create("Play Again");
    start->setSize({"30%", "5%"});
    start->setPosition({"35%", "40%"});
    start->onPress(
        [this]()
        {
            mStateHandler.switchTo(StateType::GAME_STATE);
            mStateHandler.removeState(mStateType);
        });
    gui.add(start);
}

void GameOverState::setupConntinueButton()
{
    auto continueButton = tgui::Button::create("Save score");
    continueButton->setSize({"30%", "5%"});
    continueButton->setPosition({"35%", "50%"});
    continueButton->onPress(
        [this]()
        {
            mStateHandler.switchTo(StateType::SCORE_STATE);
            mStateHandler.removeState(mStateType);
        });
    gui.add(continueButton);
}

void GameOverState::setupMainMenuButton()
{
    auto mainMenu = tgui::Button::create("Main Menu");
    mainMenu->setSize({"30%", "5%"});
    mainMenu->setPosition({"35%", "60%"});
    mainMenu->onPress(
        [this]()
        {
            mStateHandler.switchTo(StateType::MENU_STATE);
            mStateHandler.removeState(mStateType);
        });
    gui.add(mainMenu);
}

void GameOverState::setupText()
{
    auto size = context().window().getSize();
    mTitle.setColor(sf::Color::White);
    mTitle.setCharacterSize(60);
    font.loadFromFile("resources/arial.ttf");
    mTitle.setFont(font);
    mTitle.setString({"You lost!"});
    mTitle.setOrigin(mTitle.getLocalBounds().left + mTitle.getLocalBounds().width / 2.0f,
                     mTitle.getLocalBounds().top + mTitle.getLocalBounds().height / 2.0f);
    mTitle.setPosition(size.x / 2.0f, 300);

    mText.setColor(sf::Color::White);
    mText.setCharacterSize(15);
    font.loadFromFile("resources/arial.ttf");
    mText.setFont(font);
    mText.setString({"Your score is: "});
    mText.setOrigin(mText.getLocalBounds().left + mText.getLocalBounds().width / 2.0f,
                    mText.getLocalBounds().top + mText.getLocalBounds().height / 2.0f);
    mText.setPosition(sf::Vector2f(context().window().getDefaultView().getCenter()) +
                      sf::Vector2f{-12.f, 50.f});
}
