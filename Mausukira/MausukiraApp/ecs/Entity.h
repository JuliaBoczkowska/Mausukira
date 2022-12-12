#ifndef ENTITY_H
#define ENTITY_H

#include "entt/entt.hpp"
#include "scene/Scene.h"

class Entity
{
public:
    Entity() = default;

    Entity(entt::entity handle, Scene* scene);


    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        T& component = mScene->mRegistry.emplace<T>(mEntity, std::forward<Args>(args)...);
        return component;
    }

    template<typename T>
    T& GetComponent()
    {
        return mScene->mRegistry.get<T>(mEntity);
    }

    template<typename T>
    bool HasAllComponents()
    {
        return mScene->mRegistry.all_of<T>(mEntity);
    }

    template<typename T>
    void RemoveComponent()
    {
        mScene->mRegistry.remove<T>(mEntity);
    }

private:
    entt::entity mEntity{entt::null};
    Scene* mScene = nullptr;
};

#endif// ENTITY_H
