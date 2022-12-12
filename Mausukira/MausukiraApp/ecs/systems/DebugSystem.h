#ifndef DEBUGSYSTEM_H
#define DEBUGSYSTEM_H


#include "System.h"
class DebugSystem : public System
{
public:
    explicit DebugSystem(entt::registry& registry);
    void update(const sf::Time& dt) override;

    bool doOnce{true};
};


#endif// DEBUGSYSTEM_H
