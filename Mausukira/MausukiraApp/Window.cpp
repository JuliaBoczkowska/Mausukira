#include "Window.h"

Window::Window(sf::VideoMode videoMode) : mRenderWindow(videoMode, "Mausukira")
{
}

void Window::drawWindow()
{
    mRenderWindow.clear();
    mRenderWindow.display();
}

void Window::handlePolledEvents()
{
    sf::Event event;
    while(mRenderWindow.pollEvent(event))
    {
        if (event.type == sf::Event::LostFocus)
        {
            isFocused = false;
            mEventManager.setFocus(false);
        }
        else if (event.type == sf::Event::GainedFocus)
        {
            isFocused = true;
            mEventManager.setFocus(true);
        }
        else if (event.type == sf::Event::Closed)
        {
            mRenderWindow.close();
        }
        mEventManager.handleEvent(event);
    }
    mEventManager.update();
}

EventManager& Window::getEventManager()
{
    return mEventManager;
}

sf::RenderWindow& Window::getWindow()
{
    return mRenderWindow;
}