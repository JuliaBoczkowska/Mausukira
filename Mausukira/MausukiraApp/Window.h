#ifndef WINDOW_H
#define WINDOW_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "event/EventManager.h"

class Window
{
public:
    Window(sf::VideoMode mode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
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

public:
    sf::RenderWindow mRenderWindow;
    EventManager mEventManager;
    bool isFocused{true};
};

#endif//WINDOW_H
