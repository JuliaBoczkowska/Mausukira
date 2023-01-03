#include "SystemQueue.h"

SystemQueue::SystemQueue(entt::registry& registry)
    : mRegistry(registry)
{
}

void SystemQueue::handleInput(sf::Event& event)
{
    for (auto& system: mSystemsQueue)
    {
        system->handleInput(event);
    }
}

void SystemQueue::update(const sf::Time& dt)
{
    for (auto& system: mSystemsQueue)
    {
        system->update(dt);
    }


}

void SystemQueue::postUpdate(const sf::Time& dt)
{
    for (auto& system: mSystemsQueue)
    {
        system->postUpdate();
    }
}


void SystemQueue::draw(sf::RenderWindow& window)
{
    for (auto& system: mSystemsQueue)
    {
        system->draw(window);
    }
}
