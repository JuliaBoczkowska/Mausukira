#include "GameState.h"
#include "../../components/TransformComponent.h"
#include "../StateHandler.h"

GameState::GameState(StateHandler& stateManager, StateType type)
    : State(stateManager, type)
    , mContext(stateManager.context())
{
    rect.setFillColor(sf::Color::Green);
    rect.setSize(sf::Vector2f(12, 12));
}

void GameState::handleInput(sf::Event& event)
{
    auto square = mContext.activeScene.createEntity();
    mContext.activeScene.reg().emplace<TransformComponent>(square);
}

void GameState::update(const sf::Time& dt)
{
}

void GameState::draw()
{
    mContext.window().draw(rect);
}
