#ifndef SCENE_H
#define SCENE_H

#include "ecs/systems/CollisionSystem/SpatialHashing/SpatialHash.h"
#include "entt/entt.hpp"
#include "states_stack/LevelInfo.h"

class Entity;

class SystemQueue;

class MapContext;

class SharedContext;

class EnemySpawner;

class Player;

class Map;

class Scene
{
public:
    Scene(SharedContext& sharedContext, sf::View& view, bool& isPlayerDead);

    ~Scene();

    void buildScene();

    void nextLevel();

    void update(const sf::Time& deltaTime);

    void handleInput(sf::Event& event);

    void draw(sf::RenderWindow& window);

    void createPlayer();

    void createEnemy();

    void createSystems();

    /** Registry is container for all components and registries. Contains component data and entity
     * ID's*/
    SharedContext& mSharedContext;
    std::unique_ptr<entt::registry> mRegistry;
    std::unique_ptr<MapContext> mMapContext;

private:
    std::unique_ptr<SystemQueue> mSystemQueue;
    std::unique_ptr<EnemySpawner> mEnemySpawner;
    std::unique_ptr<Map> mMap;

    sf::View& mView;
    SpatialHash mSpatialGrid;
    LevelInfo mLevelInfo;
    bool& mIsPlayerDead;
    void loadTextures();
};


#endif// SCENE_H
