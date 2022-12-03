#include "Game.h"
#include "SFML/Window/Event.hpp"

Game::Game()
    : mContext(SharedContext(&mWindow, &mTextureManager))
    , mStateHandler(mContext)
{
}

void Game::run()
{
    sf::Clock clock;
    auto elapsedSinceUpdate = sf::Time::Zero;
    sf::Event event;

    while (mWindow().isOpen())
    {
        elapsedSinceUpdate +=
            clock.restart();// Returns the elapsed time since its start also restarts the clock.

        while (elapsedSinceUpdate > deltaTime)
        {
            mStateHandler.closeGameWhenNoStatesLeft();
            elapsedSinceUpdate -= deltaTime;// we subtract the desired length of this frame delta
            update(deltaTime);
            mWindow.handlePolledEvents(event);
            mStateHandler.states().begin()->get()->handleInput(event);
        }
        render();
    }
}

void Game::update(const sf::Time& deltaTime)
{
    // TODO convert sf::Time value to float type. (deltaTime.asSeconds)
    mStateHandler.states().begin()->get()->update(deltaTime);
}

void Game::render()
{
    mWindow().clear();
    mStateHandler.states().begin()->get()->draw();
    mWindow().display();
}
