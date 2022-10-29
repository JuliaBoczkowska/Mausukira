#include <iostream>
#include "Game.h"
#include "SFML/Window/Event.hpp"
#include <entt/signal/dispatcher.hpp>

//Game::Game()
//{
//    //bool addCallback(const std::string& name, std::function<void(const T&, std::unique_ptr<EventDetails>)> foo)
//    mWindow.getEventManager().addCallback("Move", [this](std::unique_ptr<EventDetails> event)
//    {
//        MoveSprite(std::move(event));
//    });
//    rect.setFillColor(sf::Color::Green);
//    rect.setSize(sf::Vector2f (12,12));
//}

void Game::MoveSprite(std::unique_ptr<EventDetails> details)
{
    sf::Vector2i mousePos = mWindow.getEventManager().getMousePos(&mWindow.getWindow());
    rect.setPosition(mousePos.x, mousePos.y);
    std::cout << "Moving sprite to: " << mousePos.x << ":" << mousePos.y << std::endl;
}

Game::Game() : mStateHandler(mContext)
{
    rect.setFillColor(sf::Color::Green);
    rect.setSize(sf::Vector2f (12,12));
}

void Game::run()
{
    sf::Clock clock;
    auto elapsedSinceUpdate = sf::Time::Zero;
    auto& window = mWindow.getWindow();

    while (window.isOpen())
    {
        elapsedSinceUpdate += clock.restart(); //Returns the elapsed time since its start also restarts the clock.

        while (elapsedSinceUpdate > deltaTime)
        {
            elapsedSinceUpdate -= deltaTime; //we subtract the desired length of this frame delta
            update();
            mWindow.handlePolledEvents();
            //before update stack might be empty
//            if (stateStack.isEmpty())
//                window.close();
        }
        render();
    }
}

void Game::update()
{
    //convert sf::Time value to float type.
    //deltaTime.asSeconds(
}

void Game::render()
{
    mWindow.getWindow().clear();
    mWindow.getWindow().draw(rect);
    mWindow.getWindow().display();

}
