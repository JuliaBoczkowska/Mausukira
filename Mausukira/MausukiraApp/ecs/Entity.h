#ifndef ENTITY_H
#define ENTITY_H

#include "entt/entt.hpp"
#include "scene/Scene.h"

class Entity
{
public:
    Entity() = default;

    Entity(entt::entity handle, Scene* scene);

public:
    template<typename T, typename... Args>
    T& addComponent(Args&&... args)
    {
        T& component = mScene->mRegistry.emplace<T>(mEntity, std::forward<Args>(args)...);
        return component;
    }

    template<typename T>
    T& getComponent()
    {
        return mScene->mRegistry.get<T>(mEntity);
    }

private:
    entt::entity mEntity{entt::null};
    Scene* mScene = nullptr;
};

#endif// ENTITY_H
