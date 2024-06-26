#include "GameState.h"
#include "states_stack/StateHandler.h"


GameState::GameState(StateHandler& stateManager, StateType type, sf::View view)
    : State(stateManager, type, view)
    , mScene(stateManager.context(), mView, isPlayerDead)
{
    mScene.buildScene();
}


void GameState::handleInput(sf::Event& event)
{
    checkIfPauseState(event);
    if (event.type == event.KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            mStateHandler.removeState(StateType::GAME_STATE);
            mStateHandler.switchTo(StateType::GAME_STATE);
        }
        if (event.key.code == sf::Keyboard::O)
        {
            mStateHandler.removeState(StateType::GAME_STATE);
            mStateHandler.switchTo(StateType::SCORE_STATE);
        }
    }
    mScene.handleInput(event);
}

void GameState::checkIfPauseState(const sf::Event& event)
{
    if (event.type == event.KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            mStateHandler.switchTo(StateType::PAUSE_STATE);
        }
    }
}

void GameState::update(const sf::Time& dt)
{
    mScene.update(dt);

    if (isPlayerDead)
    {
        mStateHandler.switchTo(StateType::GAME_OVER_STATE);
    }
}

void GameState::draw()
{
    mScene.draw(context().window());
}
