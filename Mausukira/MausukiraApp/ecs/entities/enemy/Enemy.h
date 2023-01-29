#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/ShootingComponents.h"
#include "ecs/entities/Entity.h"

struct AttackInfo
{
    AttackType mAttackType{};
    sf::Vector2f mAttackDamageMinMax{};
    sf::Vector2f mAttackSpeedMinMax{};
};

struct EnemyModelInfo
{
    std::string mName{};
    AttackInfo mAttackInfo{};
    sf::Vector2i mHealthMinMax{};
    sf::Vector2f mMovementSpeedMinMax{};
    sf::Vector2f mDecelerationSpeedMinMax{};
    float mReactionTime{};
    sf::Vector2f mActiveWanderTimeMinMax{};
    sf::Vector2f mRestTimeMinMax{};
};

struct EnemyCollider
{
    int id;
};

class Scene;

class Entity;

class Enemy
{
public:
    Enemy(Scene* scene, EntityStatistic enemyStats, const sf::Vector2i& position,
          const std::pair<std::vector<sf::Sprite>, float>& sprites);

    void setupColliderRelationship(Entity& enemy, Entity& colliderFoot, Entity& colliderBody) const;

    void prepareColliders(Entity& colliderFoot, Entity& colliderBody,
                          const std::vector<sf::Sprite>& sprites, Entity& enemy) const;
    void setupWeapon(Scene* scene, Entity& enemy) const;

    Entity enemy;
};

#endif// ENEMY_H