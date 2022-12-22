#include "Enemy.h"
#include "ecs/components/Components.h"
#include "states_stack/SharedContext.h"
#include "ecs/entities/Entity.h"

Enemy::Enemy(Scene* scene, const EntityStatistic& enemyStats, const sf::Vector2i& position,
    const std::vector<sf::Sprite>& sprites)
{
    Entity enemy = { scene->mRegistry.create(), scene };
    sf::RectangleShape rect(
        CollisionBox::setupCollider(sprites[0].getGlobalBounds(), CollisionBox::CollisionType::FOOT));
    enemy.addComponent<SpriteComponent>(sprites);
    enemy.addComponent<ColliderComponent>(rect);
    enemy.addComponent<MovableComponent>();
    enemy.addComponent<HealthComponent>(static_cast<float>(enemyStats.mHealth));
    enemy.addComponent<PositionComponent>(
        sf::Vector2f{ static_cast<float>(position.x * 32),
                      static_cast<float>(position.y * 32) });

//    enemyStats.hit = [&healthComponent](const int& damage)
//    {
//        healthComponent.damageHealth(damage);
//    };
    enemy.addComponent<EntityStatistic>(enemyStats);
    enemy.addComponent<VelocityComponent>();
}

