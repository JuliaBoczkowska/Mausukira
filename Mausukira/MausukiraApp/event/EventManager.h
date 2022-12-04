#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "EventInfo.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

using Bindings = std::unordered_map<std::string, std::unique_ptr<Binding>>;
using Callbacks =
    std::unordered_map<std::string, std::function<void(std::unique_ptr<EventDetails>)>>;

class EventManager
{
public:
    explicit EventManager() = default;
    ~EventManager();

    /**
     * @brief Add callbacks
     * @param name Name of the callback.
     * @param foo Function to be added to callbacks.
     * @return Indication if the process was successful or not
     */
    bool addCallback(const std::string& name,
                     std::function<void(std::unique_ptr<EventDetails>)> foo)
    {
        return mCallbacks.emplace(name, foo).second;
    }

    /**
     * @brief If there is no repeating names, the new binding is added into an unordered_map
     * @param binding  Associates a name of the action with the event.
     * @return
     */
    bool addBinding(std::unique_ptr<Binding> binding);

    /**
     * @brief It takes the name of the binding, searches the container and if a match is found,
     * removes the binding.
     * @param name Name of the binding.
     * @return Value indicating if the operation was successful.
     */
    bool removeBinding(std::string name);

    /**
     * @brief If the current window hasn't got focus we won't check for events.
     * @param focus Indication if the window is focused or not.
     */
    void setFocus(const bool& focus)
    {
        mHasFocus = focus;
    }


    void removeCallback(const std::string& name)
    {
        mCallbacks.erase(name);
    }

    /**
     * @brief Function responsible for processing all the polled events. It is called every
     * iteration of the program It iterates through all bindings and try to match it with the
     * current event. If the event is found its type is checked. It could be e.i. Keyboard, Joystick
     * or Mouse click.
     * @param event Polled event.
     */
    void handleEvent(sf::Event& event);

    /**
     * @brief Checks real time events like key or mouse press.
     */
    void update();

private:
    void updateCounterAndBindEventKeyCode(Binding* bind, const EventInfo& eventInfo) const;
    void checkOtherEventTypes(const sf::Event& event, Binding* bind,
                              const EventType& sfmlEvent) const;

private:
    /** Tracks if the game window has a focus*/
    bool mHasFocus{true};
    /** Bindings unordered_map */
    Bindings mBindings;
    /** Callbacks unordered_map */
    Callbacks mCallbacks;
};

#endif// EVENTMANAGER_H
