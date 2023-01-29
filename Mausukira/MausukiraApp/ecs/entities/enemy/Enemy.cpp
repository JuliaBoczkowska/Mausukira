#include "Enemy.h"
#include "ecs/Scene.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/Components.h"
#include "ecs/components/EnemyComponent.h"
#include "ecs/components/SteeringBehaviourComponent.h"
#include "ecs/entities/Entity.h"
#include "states_stack/SharedContext.h"

Enemy::Enemy(Scene* scene, EntityStatistic enemyStats, const sf::Vector2i& position,
             const std::pair<std::vector<sf::Sprite>, float>& spritesAndStats)
    : enemy(scene->mRegistry->create(), scene->mRegistry.get())
{
    Entity colliderBody = {scene->mRegistry->create(), scene->mRegistry.get()};
    Entity colliderFoot = {scene->mRegistry->create(), scene->mRegistry.get()};

    auto& [sprites, additionalArmourHealth] = spritesAndStats;
    enemy.addComponent<SpriteComponent>(sprites);
    enemy.addComponent<MovableComponent>();
    auto health = static_cast<float>(enemyStats.mHealth) + additionalArmourHealth;
    enemy.addComponent<HealthComponent>(health, health);
    enemy.addComponent<PositionComponent>(sf::Vector2f{static_cast<float>(position.x * TILE_SIZE),
                                                       static_cast<float>(position.y * TILE_SIZE)});
    enemy.addComponent<EntityStatistic>(enemyStats);
    enemy.addComponent<EntityState>(MobState::Idle);
    enemy.addComponent<VelocityComponent>();
    enemy.addComponent<AiComponent>();
    enemy.addComponent<EnemyComponent>();
    enemy.addComponent<SteeringBehaviourComponent>(
        enemyStats.mDecelerationSpeed, enemyStats.mActiveWanderTime, enemyStats.mRestTime);
    enemy.addComponent<SensorComponent>();
    enemy.addComponent<EnemyDamage>(enemyStats.mAttackDamage, enemyStats.mAttackSpeed);

    prepareColliders(colliderFoot, colliderBody, sprites, enemy);
    setupColliderRelationship(enemy, colliderFoot, colliderBody);
    if (enemyStats.mAttackType == AttackType::Ranged)
    {
        setupWeapon(scene, enemy);
    }
}

void Enemy::setupWeapon(Scene* scene, Entity& enemy) const
{
    Entity weapon = {scene->mRegistry->create(), scene->mRegistry.get()};
    const sf::Vector2f& offsetFromParent{14.f, 25.f};
    weapon.addComponent<AttachmentPoint>(enemy.getEntity(), offsetFromParent);
    weapon.addComponent<PositionComponent>(enemy.getComponent<PositionComponent>().mPosition +
                                           offsetFromParent);
    weapon.addComponent<WeaponComponent>(static_cast<WeaponType>(generateIntNumberInRange(0, 2)));
    weapon.addComponent<WeaponEnemy>();
}

void Enemy::prepareColliders(Entity& colliderFoot, Entity& colliderBody,
                             const std::vector<sf::Sprite>& sprites, Entity& enemy) const
{

    sf::RectangleShape rect(CollisionBox::setupCollider(sprites[0].getGlobalBounds(),
                                                        CollisionBox::CollisionType::FOOT));
    colliderFoot.addComponent<AttachmentPoint>(enemy.getEntity(), sf::Vector2f{20, 20});
    colliderFoot.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::FOOT, false);
    colliderFoot.addComponent<EnemyCollider>();


    rect = CollisionBox::setupCollider(sprites[0].getGlobalBounds());
    colliderBody.addComponent<ColliderComponent>(rect, CollisionBox::CollisionType::ENEMY, false);
    colliderBody.addComponent<AttachmentPoint>(enemy.getEntity(), sf::Vector2f{20, 20});
    colliderBody.addComponent<EnemyCollider>();
}

void Enemy::setupColliderRelationship(Entity& enemy, Entity& colliderFoot,
                                      Entity& colliderBody) const
{
    enemy.addComponent<Relationship>(size_t{2}, colliderBody.getEntity(), entt::null,
                                     colliderBody.getEntity());
    colliderBody.addComponent<Relationship>(size_t{0}, entt::null, enemy.getEntity(),
                                            colliderFoot.getEntity(), enemy.getEntity(),
                                            sf::Vector2f{0.f, 0.f});

    colliderFoot.addComponent<Relationship>(size_t{0}, entt::null, colliderBody.getEntity(),
                                            entt::null, enemy.getEntity(), sf::Vector2f{0.f, 0.f});
}
