#include "Window.h"
#include "SFML/Window/Event.hpp"
#include "states_stack/StateHandler.h"

Window::Window(sf::VideoMode videoMode)
    : mRenderWindow(videoMode, "Mausukira")
{
    mRenderWindow.setKeyRepeatEnabled(false);
}

void Window::handlePolledEvents(sf::Event& event, StateHandler& mStateHandler)
{
    sf::View view = mRenderWindow.getView();
    while (mRenderWindow.pollEvent(event))
    {
        mStateHandler.handleInput(event);
        if (event.type == sf::Event::Closed)
        {
            mRenderWindow.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            view.setSize(
                {static_cast<float>(event.size.width), static_cast<float>(event.size.height)});
            mRenderWindow.setView(view);
        }
    }
}

sf::RenderWindow& Window::operator()()
{
    return mRenderWindow;
}

const sf::RenderWindow& Window::operator()() const
{
    return mRenderWindow;
}
