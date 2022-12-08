#ifndef SCENE_H
#define SCENE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "ecs/systems/SystemQueue.h"
#include "map/MapContext.h"
#include "utils/TextureManager.h"
#include <entt/entt.hpp>

class Entity;
class SharedContext;

class Scene
{
public:
    Scene(SharedContext& sharedContext, MapContext& mapContext);
    ~Scene();

    void buildScene();
    void update(const sf::Time& deltaTime);
    void handleInput(sf::Event& event);
    void draw(sf::RenderWindow& window);
    void createPlayer();
    void createSystems();

private:
    friend Entity;
    /** Registry is container for all components and registries. Contains component data and entity
     * ID's*/
    entt::registry mRegistry;
    SystemQueue mSystemQueue;
    SharedContext& mSharedContext;
    MapContext& mMapContext;
};


#endif// SCENE_H
