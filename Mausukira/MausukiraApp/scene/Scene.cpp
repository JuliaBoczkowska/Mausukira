#include "Scene.h"
#include "ecs/Entity.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/Components.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/PlayerMoveSystem.h"
#include "ecs/systems/RenderingSystem.h"
#include "scene/CollisionBox.h"

Scene::Scene(TextureManager& textureManager, MapContext& mapContext)
    : mSystemQueue(mRegistry)
    , mTextureManager(textureManager)
    , mMapContext(mapContext)
{
}
void Scene::buildScene()
{
    createSystems();
    createPlayer();
}

void Scene::createSystems()
{
    mSystemQueue.addSystem<PlayerMoveSystem>();
    mSystemQueue.addSystem<CollisionSystem>(mMapContext);

    mSystemQueue.addSystem<RenderingSystem>(mMapContext);
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

void Scene::createPlayer()
{
    unsigned SPRITE_TILE_SIZE = 16;///< Tiles are 16 px wide and 16 px tall
    int TILE_SIZE = 32;            ///< Tiles are 16 px wide and 16 px tall
    unsigned SHEET_SIZE = 128u;    ///< One row consists of 8 tiles

    mTextureManager.load("PLAYER", "resources/tiles/characters.png");
    sf::Sprite mSprite;
    mSprite.setTexture(mTextureManager.get("PLAYER"));

    sf::IntRect tileBoundaries(0 % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               0 / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               SPRITE_TILE_SIZE, SPRITE_TILE_SIZE);

    mSprite.setTextureRect(tileBoundaries);
    mSprite.setScale({2, 2});

    Entity player = {mRegistry.create(), this};
    player.AddComponent<ColliderComponent>(
        "PLAYER", CollisionBox{mSprite.getGlobalBounds(), CollisionBox::COLLISION_TYPE::FOOT});
    player.AddComponent<TransformComponent>(player.GetComponent<ColliderComponent>(),
                                            mMapContext.centerOfTheFirstRoom);
    player.AddComponent<MovableComponent>();
    player.AddComponent<SpriteComponent>(player.GetComponent<TransformComponent>(), mSprite);
    player.AddComponent<EntityComponent>();
}
