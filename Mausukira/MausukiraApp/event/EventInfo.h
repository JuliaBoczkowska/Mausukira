#ifndef EVENTINFO_H
#define EVENTINFO_H

#include "EventManager.h"
#include "SFML/Window/Event.hpp"
#include <vector>


enum class EventType
{
    KeyPressed = sf::Event::KeyPressed,
    KeyReleased = sf::Event::KeyReleased,
    MouseButtonPressed = sf::Event::MouseButtonPressed,
    MouseButtonReleased = sf::Event::MouseButtonReleased,
    MouseWheelMoved = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1,
    Mouse,
    Joystick
};

struct EventInfo
{
    EventInfo()
    {
        mCode = 0;
    }
    EventInfo(int event)
    {
        mCode = event;
    }
    int mCode;
};

/**
 * @brief Helper class that makes using bind events more simple
 */
struct EventDetails
{
    EventDetails(const std::string& bindName)
        : mName(bindName)
    {
        Clear();
    }
    std::string mName;
    sf::Vector2i mSize;
    sf::Uint32 mTextEntered;
    sf::Vector2i mMouse;
    int mMouseWheelDelta;
    int mKeyCode;

    void Clear()
    {
        mSize = sf::Vector2i(0, 0);
        mTextEntered = 0;
        mMouse = sf::Vector2i(0, 0);
        mMouseWheelDelta = 0;
        mKeyCode = -1;
    }
};


/**
 * @brief Struct that represents bindings to an group of events.
 * To make the binding to key possible we need the event type and
 * the key's code
 */
struct Binding
{
    /** Vector of bind events */
    using Events = std::vector<std::pair<EventType, EventInfo>>;

    /**
     * @brief Constructor taking the name of the action that will be associated with the event.
     * @param name Name of the action
     */
    Binding(const std::string& name)
        : mName(name)
        , mDetails(name)
        , counter(0)
    {
    }

    /**
     * @brief Takes an event info and type in order to add it to the event vector
     * @param type Type of the event
     * @param info Event information like key's code e.g. sf::Keyboard::Space
     */
    void bindEvent(EventType type, EventInfo info = EventInfo())
    {
        mEvents.emplace_back(type, info);
    }

    Events mEvents;
    std::string mName;
    int counter; /** Current count of events that are taking place in real time. */
    EventDetails mDetails;
};
#endif// EVENTINFO_H
