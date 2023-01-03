
#include "Player.h"
#include "ecs/components/Components.h"
#include "states_stack/SharedContext.h"
#include "utils/SpriteSheetHandler.h"
#include "ecs/components/ShootingComponents.h"

Player::Player(Scene* scene)
{
    Entity colliderBody{ scene->mRegistry->create(), scene->mRegistry.get() };
    Entity colliderFoot = { scene->mRegistry->create(), scene->mRegistry.get() };
    Entity player{ scene->mRegistry->create(), scene->mRegistry.get() };

    scene->mSharedContext.textureManager.load("PLAYER", "resources/tiles/hero.png");
    sf::Sprite sprite = SpriteSheetHandler::extractSpriteFromTileSheet(0,
        scene->mSharedContext.textureManager.get("PLAYER"));
    sprite.setScale({ 2, 2 });
    sprite = setupPlayer(scene, sprite, player);

    setupColliders(sprite, scene, colliderFoot, colliderBody);
    setupColliderRelationship(player, colliderFoot, colliderBody);

    setupWeapon(scene, player);
}

void Player::setupWeapon(Scene* scene, Entity& player) const
{
    Entity weapon = { scene->mRegistry->create(), scene->mRegistry.get() };
    const sf::Vector2f& offsetFromParent{ 14.f, 25.f };
    weapon.addComponent<AttachmentPoint>(player.getEntity(), offsetFromParent);
    weapon.addComponent<PositionComponent>(
        player.getComponent<PositionComponent>().mPosition + offsetFromParent);
    weapon.addComponent<WeaponComponent>();
}

sf::Sprite& Player::setupPlayer(Scene* scene, sf::Sprite& sprite, Entity& player) const
{
    player.addComponent<MovableComponent>();
    player.addComponent<HealthComponent>(100);
    player.addComponent<SpriteComponent>(sprite);
    player.addComponent<PositionComponent>(
        sf::Vector2f(scene->mMapContext->mCenterOfTheFirstRoom.x, scene->mMapContext->mCenterOfTheFirstRoom.y));
    player.assignComponent<PlayerComponent>();
    player.addComponent<ScoreComponent>();
    player.addComponent<VelocityComponent>();
    return sprite;
}

void
Player::setupColliders(const sf::Sprite& sprite, Scene*& scene, Entity& colliderFoot, Entity& colliderBody) const
{
    sf::RectangleShape rect(CollisionBox::setupCollider(sprite.getGlobalBounds(), CollisionBox::CollisionType::FOOT));
    colliderFoot.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::FOOT);
    rect = CollisionBox::setupCollider(sprite.getGlobalBounds());
    colliderBody.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::BODY);
}

void Player::setupColliderRelationship(Entity& player, Entity& colliderFoot, Entity& colliderBody) const
{
    player.addComponent<Relationship>(size_t{ 2 }, colliderBody.getEntity(), entt::null, colliderBody.getEntity());
    colliderBody.addComponent<Relationship>(size_t{ 0 }, entt::null, player.getEntity(), colliderFoot.getEntity(),
        player.getEntity(),
        sf::Vector2f{ 0.f, 0.f });

    colliderFoot.addComponent<Relationship>(size_t{ 0 }, entt::null, colliderBody.getEntity(), entt::null,
        player.getEntity(),
        sf::Vector2f{ 0.f, 0.f });
}
