#include "Window.h"

Window::Window(sf::VideoMode videoMode)
    : mRenderWindow(videoMode, "Mausukira")
{
}

void Window::handlePolledEvents(sf::Event& event)
{
    sf::View view = mRenderWindow.getView();
    while (mRenderWindow.pollEvent(event))
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
        if (event.type == sf::Event::Resized)
        {
            // resize my view
            view.setSize(
                {static_cast<float>(event.size.width), static_cast<float>(event.size.height)});
            mRenderWindow.setView(view);
            // and align shape
        }
        mEventManager.handleEvent(event);
    }
    mEventManager.update();
}

EventManager& Window::getEventManager()
{
    return mEventManager;
}