#ifndef WINDOW_H
#define WINDOW_H

#include "SFML/Graphics/RenderWindow.hpp"

class StateHandler;
class Window
{
public:
    Window(sf::VideoMode mode = sf::VideoMode(1024, 1024));
    ~Window() = default;

    sf::RenderWindow& operator()();
    const sf::RenderWindow& operator()() const;
    void handlePolledEvents(sf::Event& event, StateHandler& mStateHandler);

public:
    sf::RenderWindow mRenderWindow;
};

#endif// WINDOW_H
