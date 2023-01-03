#ifndef SYSTEMQUEUE_H
#define SYSTEMQUEUE_H

#include "System.h"
#include <queue>

class SystemQueue
{
public:
    SystemQueue(entt::registry& registry);

    template<typename System, typename... Args>
    void addSystem(Args& ... args)
    {
        mSystemsQueue.emplace_back(
            std::unique_ptr<System>(std::make_unique<System>(mRegistry, args...)));
    }

    void handleInput(sf::Event& event);

    void update(const sf::Time& dt);

    void postUpdate(const sf::Time& dt);

    void draw(sf::RenderWindow& window);

private:
    std::deque<std::unique_ptr<System>> mSystemsQueue;
    entt::registry& mRegistry;
};


#endif// SYSTEMQUEUE_H
