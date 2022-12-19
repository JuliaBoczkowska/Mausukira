
#include "Player.h"
#include "ecs/Entity.h"
#include "ecs/components/Components.h"
#include "ecs/components/weapon/Weapon.h"

Player::Player(Scene* scene)
{
    Entity player = {scene->mRegistry.create(), scene};
    unsigned SPRITE_TILE_SIZE = 16;///< Tiles are 16 px wide and 16 px tall
    unsigned SHEET_SIZE = 128u;    ///< One row consists of 8 tiles

    scene->mSharedContext.textureManager.load("PLAYER", "resources/tiles/hero.png");
    sf::Sprite mSprite;
    mSprite.setTexture(scene->mSharedContext.textureManager.get("PLAYER"));

    sf::IntRect tileBoundaries(0 % (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               0 / (SHEET_SIZE / SPRITE_TILE_SIZE) * SPRITE_TILE_SIZE,
                               SPRITE_TILE_SIZE, SPRITE_TILE_SIZE);

    mSprite.setTextureRect(tileBoundaries);
    mSprite.setScale({2, 2});
    float health = 100;

    player.addComponent<ColliderComponent>(
        "PLAYER", CollisionBox{mSprite.getGlobalBounds(), CollisionBox::CollisionType::FOOT});
    player.addComponent<MovableComponent>();
    player.addComponent<HealthComponent>(health);
    player.addComponent<SpriteComponent>(mSprite);
    player.addComponent<TransformComponent>(
        player.getComponent<ColliderComponent>(), player.getComponent<SpriteComponent>(),
        player.getComponent<HealthComponent>(), scene->mMapContext.centerOfTheFirstRoom);
    player.addComponent<PlayerComponent>();
    player.addComponent<Weapon>(&scene->mSharedContext.window());
    player.addComponent<ScoreComponent>();
}
