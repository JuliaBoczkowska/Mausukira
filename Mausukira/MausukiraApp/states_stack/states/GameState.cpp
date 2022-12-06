#include "GameState.h"
#include "../../ecs/Entity.h"
#include "../StateHandler.h"

GameState::GameState(StateHandler& stateManager, StateType type, sf::View view)
    : State(stateManager, type, view)
    , mMap(stateManager.context(), mMapContext)
    , mScene(stateManager.context().textureManager, mMapContext)
{
    mScene.buildScene();
}

void GameState::handleInput(sf::Event& event)
{
    mScene.handleInput(event);
}

void GameState::update(const sf::Time& dt)
{
    mMap.update(dt);
    mScene.update(dt);
}

void GameState::draw()
{
    mMap.draw(context().window.mRenderWindow);
    mScene.draw(context().window.mRenderWindow);
}
