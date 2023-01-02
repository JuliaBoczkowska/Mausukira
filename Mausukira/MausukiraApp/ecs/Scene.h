#ifndef SCENE_H
#define SCENE_H

#include "ecs/entities/enemy/EnemyParser.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "ecs/entities/enemy/EnemySpawner.h"
#include "ecs/systems/SystemQueue.h"
#include "utils/TextureManager.h"
#include "entt/entt.hpp"
#include "dungeon/map/MapContext.h"
#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"

class Entity;

class SharedContext;

class Player;

class Scene
{
public:
    Scene(SharedContext& sharedContext, MapContext& mapContext);

    ~Scene() = default;

    void buildScene();

    void update(const sf::Time& deltaTime);

    void handleInput(sf::Event& event);

    void draw(sf::RenderWindow& window);

    void createPlayer();

    void createEnemy();

    void createSystems();

    /** Registry is container for all components and registries. Contains component data and entity
     * ID's*/
    entt::registry mRegistry;
    friend Entity;
    friend Player;
    friend EnemySpawner;
private:
    SharedContext& mSharedContext;
    SystemQueue mSystemQueue;
    MapContext& mMapContext;
    EnemySpawner mEnemySpawner;
    SpatialHash mSpatialGrid;
};


#endif// SCENE_H
