
#include "Player.h"
#include "Entity.h"
#include "ecs/components/Components.h"
#include "states_stack/SharedContext.h"
#include "utils/SpriteSheetHandler.h"

Player::Player(Scene* scene)
{
    Entity player = { scene->mRegistry.create(), scene };
    float health = 100;

    scene->mSharedContext.textureManager.load("PLAYER", "resources/tiles/hero.png");
    sf::Sprite sprite = SpriteSheetHandler::extractSpriteFromTileSheet(0,
        scene->mSharedContext.textureManager.get("PLAYER"));

    sf::RectangleShape rect(CollisionBox::setupCollider(sprite.getGlobalBounds(), CollisionBox::CollisionType::FOOT));
    player.addComponent<ColliderComponent>(rect);
    player.addComponent<MovableComponent>();
    player.addComponent<HealthComponent>(health);
    player.addComponent<SpriteComponent>(sprite);
    player.addComponent<PositionComponent>(scene->mMapContext.centerOfTheFirstRoom);
    player.addComponent<PlayerComponent>();
    player.addComponent<ScoreComponent>();
    player.addComponent<VelocityComponent>();
}
