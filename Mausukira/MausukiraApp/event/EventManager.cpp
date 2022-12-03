#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

EventManager::~EventManager()
{
}

sf::Vector2i getMousePos(sf::RenderWindow* window)
{
    return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
}

bool EventManager::addBinding(std::unique_ptr<Binding> binding)
{
    if (mBindings.find(binding->mName) != mBindings.end())
    {
        return false;
    }
    return mBindings.emplace(binding->mName, std::move(binding)).second;
}

bool EventManager::removeBinding(std::string name)
{
    auto itr = mBindings.find(name);
    if (itr == mBindings.end())
    {
        return false;
    }
    mBindings.erase(itr);
    return true;
}

void EventManager::handleEvent(sf::Event& event)
{
    for (auto& bindIter: mBindings)
    {
        Binding* bind = bindIter.second.get();
        for (auto& eventIter: bind->mEvents)
        {
            auto sfmlEvent = static_cast<EventType>(event.type);
            const auto& [bindEventType, eventInfo] = eventIter;

            if (bindEventType != sfmlEvent)
            {
                continue;
            }

            if (sfmlEvent == EventType::KeyPressed || sfmlEvent == EventType::KeyReleased)
            {
                if (eventInfo.mCode == event.key.code)
                {
                    updateCounterAndBindEventKeyCode(bind, eventInfo);
                    break;
                }
            }
            else if (sfmlEvent == EventType::MouseButtonPressed ||
                     sfmlEvent == EventType::MouseButtonReleased)
            {
                if (eventInfo.mCode == event.mouseButton.button)
                {
                    bind->mDetails.mMouse.x = event.mouseButton.x;
                    bind->mDetails.mMouse.y = event.mouseButton.y;
                    updateCounterAndBindEventKeyCode(bind, eventInfo);
                    break;
                }
            }
            else
            {
                checkOtherEventTypes(event, bind, sfmlEvent);
            }
        }
    }
}

void EventManager::checkOtherEventTypes(const sf::Event& event, Binding* bind,
                                        const EventType& sfmlEvent) const
{
    if (sfmlEvent == EventType::MouseWheelMoved)
    {
        bind->mDetails.mMouseWheelDelta = event.mouseWheel.delta;
    }
    else if (sfmlEvent == EventType::WindowResized)
    {
        bind->mDetails.mSize.x = event.size.width;
        bind->mDetails.mSize.y = event.size.height;
    }
    else if (sfmlEvent == EventType::TextEntered)
    {
        bind->mDetails.mTextEntered = event.text.unicode;
    }
    ++(bind->counter);
}

void EventManager::update()
{
    if (!mHasFocus)
    {
        return;
    }
    for (auto& bindIter: mBindings)
    {
        auto bind = bindIter.second.get();
        for (auto& eventIter: bind->mEvents)
        {
            const auto& [eventType, eventKeyCode] = eventIter;
            switch (eventType)
            {
                case (EventType::Keyboard):
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eventKeyCode.mCode)))
                    {
                        updateCounterAndBindEventKeyCode(bind, eventKeyCode);
                    }
                    break;
                case (EventType::Mouse):
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eventKeyCode.mCode)))
                    {
                        updateCounterAndBindEventKeyCode(bind, eventKeyCode);
                    }
                    break;
            }
        }
        if (bind->mEvents.size() == bind->counter)
        {
            auto callItr = mCallbacks.find(bind->mName);
            if (callItr != mCallbacks.end())
            {
                callItr->second(static_cast<std::unique_ptr<EventDetails>>(&bind->mDetails));
            }
        }
        bind->counter = 0;
        bind->mDetails.Clear();
    }
}

void EventManager::updateCounterAndBindEventKeyCode(Binding* bind,
                                                    const EventInfo& eventKeyCode) const
{
    if (bind->mDetails.mKeyCode != -1)
    {
        bind->mDetails.mKeyCode = eventKeyCode.mCode;
    }
    ++(bind->counter);
}
