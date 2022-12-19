#include "Scene.h"
#include "Player.h"
#include "ecs/systems/Systems.h"
#include "states_stack/SharedContext.h"

Scene::Scene(SharedContext& sharedContext, MapContext& mapContext)
    : mSystemQueue(mRegistry)
    , mSharedContext(sharedContext)
    , mMapContext(mapContext)
    , mEnemySpawner(mSharedContext.textureManager)
{
}

void Scene::buildScene()
{
    createSystems();
    createPlayer();
    EnemyParser::loadEnemies(mEnemySpawner);
    createEnemy();
}

void Scene::createSystems()
{
    mSystemQueue.addSystem<RenderingSystem>(mMapContext);
    mSystemQueue.addSystem<CollisionSystem>(mMapContext);
    mSystemQueue.addSystem<PlayerMoveSystem>();
    mSystemQueue.addSystem<AttackSystem>(mSharedContext);
    mSystemQueue.addSystem<ScoreSystem>();
    mSystemQueue.addSystem<CameraSystem>(mSharedContext, mMapContext);
    mSystemQueue.addSystem<DebugSystem>();
}

Scene::~Scene()
{
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
