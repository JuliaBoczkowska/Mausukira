#ifndef SCENE_H
#define SCENE_H

#include "SFML/System/Time.hpp"
#include <entt/entt.hpp>

class Entity;

class Scene
{
public:
    Scene();

    ~Scene();

    void update(const sf::Time& deltaTime);

    Entity createEntity();

private:
    friend Entity;
    /** Registry is container for all components and registries. Contains component data and entity ID's*/
    entt::registry mRegistry;
};


#endif//SCENE_H
