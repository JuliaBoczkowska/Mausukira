#ifndef ENTITY_H
#define ENTITY_H

#include "entt/entt.hpp"
#include "ecs/Scene.h"

class Entity
{
public:
    Entity(entt::entity handle, entt::registry* registry);

public:
    template<typename T, typename... Args>
    T& addComponent(Args&& ... args)
    {
        T& component = mRegistry.emplace<T>(mEntity, std::forward<Args>(args)...);
        return component;
    }

    template<typename T>
    T& getComponent()
    {
        T& component = mRegistry.get<T>(mEntity);
        return component;
    }


    template<typename T>
    void assignComponent()
    {
        mRegistry.emplace<T>(mEntity);
    }

    entt::entity& getEntity()
    {
        return mEntity;
    }

private:
    entt::entity mEntity{ entt::null };
    entt::registry& mRegistry;
};

#endif// ENTITY_H
