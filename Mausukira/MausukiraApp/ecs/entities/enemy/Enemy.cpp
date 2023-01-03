#include "Enemy.h"
#include "ecs/components/Components.h"
#include "states_stack/SharedContext.h"
#include "ecs/entities/Entity.h"

Enemy::Enemy(Scene* scene, EntityStatistic enemyStats, const sf::Vector2i& position,
    const std::vector<sf::Sprite>& sprites)
    :
    enemy(scene->mRegistry->create(), scene->mRegistry.get())
{
    Entity colliderBody = { scene->mRegistry->create(), scene->mRegistry.get() };
    Entity colliderFoot = { scene->mRegistry->create(), scene->mRegistry.get() };

    enemy.addComponent<SpriteComponent>(sprites);
    enemy.addComponent<MovableComponent>();
    enemy.addComponent<HealthComponent>(static_cast<float>(enemyStats.mHealth));
    enemy.addComponent<PositionComponent>(
        sf::Vector2f{ static_cast<float>(position.x * TILE_SIZE),
                      static_cast<float>(position.y * TILE_SIZE) });
    enemy.addComponent<EntityStatistic>(enemyStats);
    enemy.addComponent<EntityState>(MobState::Idle);
    enemy.addComponent<VelocityComponent>();
    prepareColliders(colliderFoot, colliderBody, sprites, enemy);
    setupColliderRelationship(enemy, colliderFoot, colliderBody);
}

void Enemy::prepareColliders(Entity& colliderFoot, Entity& colliderBody, const std::vector<sf::Sprite>& sprites,
    Entity& enemy) const
{

    sf::RectangleShape rect(
        CollisionBox::setupCollider(sprites[0].getGlobalBounds(), CollisionBox::CollisionType::FOOT));
    colliderFoot.addComponent<AttachmentPoint>(enemy.getEntity(), sf::Vector2f{ 20, 20 });
    colliderFoot.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::FOOT);
    colliderFoot.addComponent<EnemyCollider>();


    rect = CollisionBox::setupCollider(sprites[0].getGlobalBounds());
    colliderBody.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::ENEMY);
    colliderBody.addComponent<AttachmentPoint>(enemy.getEntity(), sf::Vector2f{ 20, 20 });
    colliderBody.addComponent<EnemyCollider>();
}

void Enemy::setupColliderRelationship(Entity& enemy, Entity& colliderFoot, Entity& colliderBody) const
{
    enemy.addComponent<Relationship>(size_t{ 2 }, colliderBody.getEntity(), entt::null, colliderBody.getEntity());
    colliderBody.addComponent<Relationship>(size_t{ 0 }, entt::null, enemy.getEntity(), colliderFoot.getEntity(),
        enemy.getEntity(),
        sf::Vector2f{ 0.f, 0.f });

    colliderFoot.addComponent<Relationship>(size_t{ 0 }, entt::null, colliderBody.getEntity(), entt::null,
        enemy.getEntity(),
        sf::Vector2f{ 0.f, 0.f });
}


