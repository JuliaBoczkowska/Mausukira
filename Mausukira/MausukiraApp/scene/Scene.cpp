#include "Scene.h"
#include "ecs/Entity.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/Components.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/weapon/Weapon.h"
#include "ecs/systems/AtttackSystem.h"
#include "ecs/systems/CameraSystem.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/DebugSystem.h"
#include "ecs/systems/PlayerMoveSystem.h"
#include "ecs/systems/RenderingSystem.h"
#include "scene/CollisionBox.h"
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
    mEnemySpawner.createEnemy(this);
}

void Scene::createPlayer()
{
    unsigned SPRITE_TILE_SIZE = 16;///< Tiles are 16 px wide and 16 px tall
    int TILE_SIZE = 32;            ///< Tiles are 16 px wide and 16 px tall
    unsigned SHEET_SIZE = 128u;    ///< One row consists of 8 tiles

    mSharedContext.textureManager.load("PLAYER", "resources/tiles/characters.png");
    sf::Sprite mSprite;
    mSprite.setTexture(mSharedContext.textureManager.get("PLAYER"));

    sf::IntRect tileBoundaries(8 % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               8 / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               SPRITE_TILE_SIZE, SPRITE_TILE_SIZE);

    mSprite.setTextureRect(tileBoundaries);
    mSprite.setScale({2, 2});
    float health = 100;

    Entity player = {mRegistry.create(), this};
    player.AddComponent<ColliderComponent>(
        "PLAYER", CollisionBox{mSprite.getGlobalBounds(), CollisionBox::COLLISION_TYPE::FOOT});
    player.AddComponent<MovableComponent>();
    player.AddComponent<HealthComponent>(health);
    player.AddComponent<SpriteComponent>(mSprite);
    player.AddComponent<TransformComponent>(
        player.GetComponent<ColliderComponent>(), player.GetComponent<SpriteComponent>(),
        player.GetComponent<HealthComponent>(), mMapContext.centerOfTheFirstRoom);
    player.AddComponent<PlayerComponent>();

    player.AddComponent<Weapon>(mSharedContext.window());
}
