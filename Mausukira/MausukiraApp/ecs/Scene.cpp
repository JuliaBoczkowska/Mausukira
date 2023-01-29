#include "Scene.h"
#include "dungeon/map/Map.h"
#include "dungeon/map/MapContext.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/entities/Player.h"
#include "ecs/entities/enemy/EnemyParser.h"
#include "ecs/entities/enemy/EnemySpawner.h"
#include "ecs/systems/AiSystem/EnemySystems/EnemyStateSystem.h"
#include "ecs/systems/AiSystem/ai/SensorSystem.h"
#include "ecs/systems/SystemQueue.h"
#include "ecs/systems/Systems.h"
#include "states_stack/SharedContext.h"

Scene::Scene(SharedContext& sharedContext, sf::View& view, bool& isPlayerDead)
    : mSystemQueue(std::make_unique<SystemQueue>(*mRegistry))
    , mIsPlayerDead(isPlayerDead)
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
    loadTextures();
}

void Scene::createSystems()
{
    mSystemQueue->addSystem<RenderingSystem>(*mMapContext.get());
    mSystemQueue->addSystem<ProjectileShootSystem>(mSharedContext, mSpatialGrid);
    mSystemQueue->addSystem<HealthSystem>();
    mSystemQueue->addSystem<CollisionSystem>(*mMapContext.get(), mSpatialGrid);
    mSystemQueue->addSystem<MoveSystem>();
    mSystemQueue->addSystem<ScoreSystem>(mSharedContext);
    mSystemQueue->addSystem<CameraSystem>(mSharedContext, *mMapContext.get(), mView);
    mSystemQueue->addSystem<DebugSystem>();
    mSystemQueue->addSystem<LevelChangeSystem>(mLevelInfo, mSharedContext.textureManager);
    mSystemQueue->addSystem<EnemyStateSystem>(*mMapContext.get(), mEnemySpawner->mEnemyEntity);
    mSystemQueue->addSystem<SensorSystem>(*mMapContext.get());
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

        auto view = mRegistry->view<PlayerComponent>();
        for (auto& entity: view)
        {
            auto [player] = view.get(entity);
            if (player.isDead)
            {
                mIsPlayerDead = true;
            }
        }
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
    (Player(this, mSharedContext, mLevelInfo));
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
    mSharedContext.score = mLevelInfo.score;
    mSharedContext.levelNumber = mLevelInfo.levelNumber;
}

Scene::~Scene()
{
}

void Scene::loadTextures()
{
    mSharedContext.textureManager.load("DOOR", "resources/tiles/door.png");
    mSharedContext.textureManager.load("GRAVE", "resources/tiles/grave.png");
}
