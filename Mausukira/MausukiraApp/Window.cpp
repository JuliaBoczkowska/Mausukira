#include "Window.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "states_stack/StateHandler.h"
#include <iostream>

Window::Window(sf::VideoMode videoMode)
    : mRenderWindow(videoMode, "Mausukira")
{
}

void Window::handlePolledEvents(sf::Event& event, StateHandler& mStateHandler)
{
    sf::View view = mRenderWindow.getView();
    while (mRenderWindow.pollEvent(event))
    {
        mStateHandler.currentState().handleInput(event);
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
sf::FloatRect Window::getViewSpace()
{
    sf::Vector2f viewCenter = mRenderWindow.getView().getCenter();
    sf::Vector2f viewSize = mRenderWindow.getView().getSize();
    sf::Vector2f viewSizeHalf(viewSize.x / 4, viewSize.y / 4);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    return viewSpace;
}

sf::RenderWindow& Window::operator()()
{
    return mRenderWindow;
}

const sf::RenderWindow& Window::operator()() const
{
    return mRenderWindow;
}
