#include "Scene.h"
#include "ecs/entities/Player.h"
#include "ecs/systems/Systems.h"
#include "states_stack/SharedContext.h"
#include "ecs/systems/MoveSystem/MoveSystem.h"

Scene::Scene(SharedContext& sharedContext, MapContext& mapContext)
    : mSystemQueue(mRegistry)
    , mSharedContext(sharedContext)
    , mMapContext(mapContext)
    , mEnemySpawner(mSharedContext.textureManager)
{
}

void Scene::buildScene()
{
    createPlayer();
    EnemyParser::loadEnemies(mEnemySpawner);
    createEnemy();
    createSystems();
}

void Scene::createSystems()
{
    mSystemQueue.addSystem<RenderingSystem>(mMapContext);
    mSystemQueue.addSystem<ProjectileShootSystem>(mSharedContext, mSpatialGrid);
    mSystemQueue.addSystem<CollisionSystem>(mMapContext, mSpatialGrid);
    mSystemQueue.addSystem<MoveSystem>();
    mSystemQueue.addSystem<ScoreSystem>();
    mSystemQueue.addSystem<CameraSystem>(mSharedContext, mMapContext);
    mSystemQueue.addSystem<DebugSystem>();
}

void Scene::update(const sf::Time& deltaTime)
{
    mSystemQueue.update(deltaTime);
}

void Scene::handleInput(sf::Event& event)
{
    mSystemQueue.handleInput(event);
}

void Scene::draw(sf::RenderWindow& window)
{
    mSystemQueue.draw(window);
}

void Scene::createEnemy()
{
    mEnemySpawner.addEnemyEntity(this);
}

void Scene::createPlayer()
{
    Player player(this);
}
