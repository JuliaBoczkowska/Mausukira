#include "Game.h"
#include "SFML/Window/Event.hpp"
#include "Window.h"
#include "states_stack/SharedContext.h"
#include "states_stack/StateHandler.h"
#include "utils/TextureManager.h"


Game::Game()
    : mContext(std::make_unique<SharedContext>(*mWindow, *mTextureManager))
    , mWindow(std::make_unique<Window>())
    , mTextureManager(std::make_unique<TextureManager>())
{
}

void Game::run()
{
    auto mStateHandler = std::make_unique<StateHandler>(*mContext);
    sf::Clock clock;
    auto elapsedSinceUpdate = sf::Time::Zero;
    sf::Event event;

    while ((*mWindow)().isOpen())
    {
        /** Returns the elapsed time since its start and restarts the clock. */
        elapsedSinceUpdate += clock.restart();
        while (elapsedSinceUpdate > deltaTime)
        {
            /** Subtract the desired length of this frame delta */
            elapsedSinceUpdate -= deltaTime;

            handlePolledEvents(event, mStateHandler);
            update(deltaTime, mStateHandler);
        }
        render(mStateHandler);
        lateUpdate(mStateHandler);
    }
}

void Game::lateUpdate(std::unique_ptr<StateHandler>& mStateHandler)
{
    mStateHandler->processQueue();
}

void Game::handlePolledEvents(sf::Event& event, std::unique_ptr<StateHandler>& mStateHandler)
{
    mWindow->handlePolledEvents(event, *mStateHandler);
}

void Game::update(const sf::Time& deltaTime, std::unique_ptr<StateHandler>& mStateHandler)
{
    mStateHandler->update(deltaTime);
}

void Game::render(std::unique_ptr<StateHandler>& mStateHandler)
{
    (*mWindow)().clear();
    mStateHandler->draw();
    (*mWindow)().display();
}

Game::~Game()
{
}