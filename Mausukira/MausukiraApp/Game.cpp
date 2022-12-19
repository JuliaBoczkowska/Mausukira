#include "Game.h"
#include "SFML/Window/Event.hpp"

Game::Game()
    : mContext(SharedContext(mWindow, mTextureManager))
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
        /** Returns the elapsed time since its start and restarts the clock. */
        elapsedSinceUpdate += clock.restart();
        while (elapsedSinceUpdate > deltaTime)
        {
            /** Subtract the desired length of this frame delta */
            elapsedSinceUpdate -= deltaTime;

            handlePolledEvents(event);
            update(deltaTime);
        }
        render();
        lateUpdate();
    }
}
void Game::lateUpdate()
{
    mStateHandler.processQueue();
}

void Game::handlePolledEvents(sf::Event& event)
{
    mWindow.handlePolledEvents(event, mStateHandler);
}

void Game::update(const sf::Time& deltaTime)
{
    mStateHandler.update(deltaTime);
}

void Game::render()
{
    mWindow().clear();
    mStateHandler.draw();
    mWindow().display();
}
