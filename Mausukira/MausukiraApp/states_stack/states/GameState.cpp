#include "GameState.h"
#include "../../ecs/Entity.h"
#include "../StateHandler.h"

GameState::GameState(StateHandler& stateManager, StateType type, sf::View view)
    : State(stateManager, type, view)
    , mContext(stateManager.context())
    , map(&stateManager.context())
{
    rect.setFillColor(sf::Color::Green);
    rect.setSize(sf::Vector2f(12, 12));
}

void GameState::handleInput(sf::Event& event)
{
    auto square = mContext.activeScene.createEntity();
    //    mContext.activeScene.reg().emplace<TransformComponent>(square);
}

void GameState::update(const sf::Time& dt)
{
    map.update(dt);
}

void GameState::draw()
{
    mContext.window->mRenderWindow.draw(rect);
    map.draw(&mContext.window->mRenderWindow);
}
