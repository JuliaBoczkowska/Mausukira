#include "Enemy.h"
#include "ecs/components/Components.h"
#include "states_stack/SharedContext.h"
#include "ecs/entities/Entity.h"

Enemy::Enemy(Scene* scene, const EntityStatistic& enemyStats, const sf::Vector2i& position,
    const std::vector<sf::Sprite>& sprites)
{
    Entity enemy = { scene->mRegistry.create(), &scene->mRegistry };
    enemy.addComponent<SpriteComponent>(sprites);
    enemy.addComponent<MovableComponent>();
    enemy.addComponent<HealthComponent>(static_cast<float>(enemyStats.mHealth));
    enemy.addComponent<PositionComponent>(
        sf::Vector2f{ static_cast<float>(position.x * 32),
                      static_cast<float>(position.y * 32) });

    enemy.addComponent<EntityStatistic>(enemyStats);
    enemy.addComponent<VelocityComponent>();

    prepareColliders(scene, sprites, enemy);
}

void Enemy::prepareColliders(Scene* scene, const std::vector<sf::Sprite>& sprites, Entity& enemy) const
{
    Entity colliderFoot = { scene->mRegistry.create(), &scene->mRegistry };
    sf::RectangleShape rect(
        CollisionBox::setupCollider(sprites[0].getGlobalBounds(), CollisionBox::CollisionType::FOOT));
    colliderFoot.addComponent<AttachmentPoint>(enemy.getEntity(), sf::Vector2f{ 20, 20 });
    colliderFoot.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::FOOT);
    colliderFoot.addComponent<EnemyCollider>();

    Entity colliderBody = { scene->mRegistry.create(), &scene->mRegistry };
    rect = CollisionBox::setupCollider(sprites[0].getGlobalBounds());
    colliderBody.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::ENEMY);
    colliderBody.addComponent<AttachmentPoint>(enemy.getEntity(), sf::Vector2f{ 20, 20 });
    colliderBody.addComponent<EnemyCollider>();
}

