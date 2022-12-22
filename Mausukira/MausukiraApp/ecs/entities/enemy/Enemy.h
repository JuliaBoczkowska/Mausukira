#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/System/Vector2.hpp"
#include "ecs/components/EntityComponent.h"
#include "SFML/Graphics/Sprite.hpp"
#include <map>

struct AttackInfo
{
    AttackType attackType{};
    sf::Vector2f attackDamageMinMax{};
    sf::Vector2f attackSpeedMinMax{};
};

struct EnemyModelInfo
{
    std::string name{};
    AttackInfo mAttackInfo{};
    sf::Vector2i healthMinMax{};
    sf::Vector2f movementSpeedMinMax{};
    float reactionTime{};
};

class Scene;

class Enemy
{
public:
    Enemy(Scene* scene, const EntityStatistic& enemyStats, const sf::Vector2i& position,
        const std::vector<sf::Sprite>& sprites);

};

#endif// ENEMY_H