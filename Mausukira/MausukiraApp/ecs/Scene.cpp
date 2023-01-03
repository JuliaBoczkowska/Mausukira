#include "Scene.h"
#include "ecs/entities/Player.h"
#include "ecs/systems/Systems.h"
#include "states_stack/SharedContext.h"
#include "dungeon/map/Map.h"

Scene::Scene(SharedContext& sharedContext, sf::View& view)
    : mSystemQueue(std::make_unique<SystemQueue>(*mRegistry))
    , mSharedContext(sharedContext)
    , mMapContext(std::make_unique<MapContext>())
    , mEnemySpawner(std::make_unique<EnemySpawner>(mSharedContext.textureManager))
    , mView(view)
    , mMap(std::make_unique<Map>(sharedContext, *mMapContext))
    , mRegistry(std::make_unique<entt::registry>())
{
}

void Scene::buildScene()
{
    createPlayer();
    EnemyParser::loadEnemies(*mEnemySpawner);
    createEnemy();
    createSystems();
}

void Scene::createSystems()
{
    mSystemQueue->addSystem<RenderingSystem>(*mMapContext.get());
    mSystemQueue->addSystem<ProjectileShootSystem>(mSharedContext, mSpatialGrid);
    mSystemQueue->addSystem<HealthSystem>();
    mSystemQueue->addSystem<CollisionSystem>(*mMapContext.get(), mSpatialGrid);
    mSystemQueue->addSystem<MoveSystem>();
    mSystemQueue->addSystem<ScoreSystem>();
    mSystemQueue->addSystem<CameraSystem>(mSharedContext, *mMapContext.get(), mView);
    mSystemQueue->addSystem<DebugSystem>();
    mSystemQueue->addSystem<LevelChangeSystem>(mLevelInfo);
}

void Scene::update(const sf::Time& deltaTime)
{
    if (mLevelInfo.changeNextLevel)
    {
        nextLevel();
    }
    else
    {
        mSystemQueue->update(deltaTime);
        mSystemQueue->postUpdate(deltaTime);
    }
}

void Scene::handleInput(sf::Event& event)
{
    mSystemQueue->handleInput(event);
}

void Scene::draw(sf::RenderWindow& window)
{
    mMap->draw(window);
    mSystemQueue->draw(window);
}

void Scene::createEnemy()
{
    mEnemySpawner->addEnemyEntity(this);
}

void Scene::createPlayer()
{
    Player player(this);
}

void Scene::nextLevel()
{
    mRegistry = std::make_unique<entt::registry>();
    mMapContext = std::make_unique<MapContext>();
    mMap = std::make_unique<Map>(mSharedContext, *mMapContext.get());
    mEnemySpawner = std::make_unique<EnemySpawner>(mSharedContext.textureManager);
    mSystemQueue = std::make_unique<SystemQueue>(*mRegistry);
    buildScene();
    mLevelInfo.changeNextLevel = false;
    mLevelInfo.levelNumber++;
}
