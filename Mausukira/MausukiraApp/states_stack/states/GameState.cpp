#include "GameState.h"
#include "ecs/Entity.h"
#include "states_stack/StateHandler.h"

GameState::GameState(StateHandler& stateManager, StateType type, sf::View view)
    : State(stateManager, type, view)
    , mMap(stateManager.context(), mMapContext)
    , mScene(stateManager.context(), mMapContext)
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
    mMap.update(dt);
    mScene.update(dt);
}

void GameState::draw()
{
    mMap.draw(context().window());
    mScene.draw(context().window());
}
