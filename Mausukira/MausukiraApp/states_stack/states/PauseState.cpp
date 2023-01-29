#include "PauseState.h"
#include "states_stack/StateHandler.h"

PauseState::PauseState(StateHandler& stateManager, StateType type, sf::View view,
                       bool isTransparent)
    : State(stateManager, type, view, isTransparent)
{
    setupBackground();
    setupText();
}

void PauseState::setupBackground()
{
    background.setSize(sf::Vector2f(context().window().getView().getSize()));
    background.setOrigin(
        background.getLocalBounds().left + background.getLocalBounds().width / 2.0f,
        background.getLocalBounds().top + background.getLocalBounds().height / 2.0f);
    background.setPosition(sf::Vector2f(context().window().getView().getCenter()));
    background.setFillColor(sf::Color(0, 0, 0, 100));
}

void PauseState::setupText()
{
    mText.setColor(sf::Color::White);
    mText.setCharacterSize(50);
    font.loadFromFile("resources/arial.ttf");
    mText.setFont(font);
    mText.setString({"Paused"});
    mText.setOrigin(mText.getLocalBounds().left + mText.getLocalBounds().width / 2.0f,
                    mText.getLocalBounds().top + mText.getLocalBounds().height / 2.0f);
    mText.setPosition(sf::Vector2f(context().window().getDefaultView().getCenter()));

    mPaused.setColor(sf::Color::White);
    mPaused.setCharacterSize(30);
    font.loadFromFile("resources/arial.ttf");
    mPaused.setFont(font);
    mPaused.setString({"Click esc to continue"});
    mPaused.setOrigin(mText.getLocalBounds().left + mText.getLocalBounds().width / 2.0f,
                      mText.getLocalBounds().top + mText.getLocalBounds().height / 2.0f);
    mPaused.setPosition(sf::Vector2f(context().window().getDefaultView().getCenter()) +
                        sf::Vector2f{-80.f, 100.f});
}

void PauseState::handleInput(sf::Event& event)
{
    if (event.type == event.KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            mStateHandler.removeState(mStateType);
        }
    }
}

void PauseState::update(const sf::Time& dt)
{
}

void PauseState::draw()
{
    context().window().draw(background);

    context().window().setView(context().window().getDefaultView());
    context().window().draw(mPaused);
    context().window().draw(mText);
    context().window().setView(mView);
}
