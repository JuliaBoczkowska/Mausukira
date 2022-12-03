#ifndef WINDOW_H
#define WINDOW_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "event/EventManager.h"

class Window
{
public:
    //    Window(sf::VideoMode mode = sf::VideoMode(sf::VideoMode::getDesktopMode().width,
    //        sf::VideoMode::getDesktopMode().height));
    Window(sf::VideoMode mode = sf::VideoMode(1024, 1024));

    ~Window() = default;

    sf::RenderWindow& operator()()
    {
        return mRenderWindow;
    }

    const sf::RenderWindow& operator()() const
    {
        return mRenderWindow;
    }

    EventManager& getEventManager();

    void handlePolledEvents(sf::Event& event);

    sf::FloatRect getViewSpace()
    {
        sf::Vector2f viewCenter = mRenderWindow.getView().getCenter();
        sf::Vector2f viewSize = mRenderWindow.getView().getSize();
        sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
        sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
        return viewSpace;
    }

public:
    sf::RenderWindow mRenderWindow;
    EventManager mEventManager;
    bool isFocused{true};
};

#endif// WINDOW_H
