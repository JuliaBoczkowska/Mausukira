#ifndef ENEMY_H
#define ENEMY_H
#include "SFML/System/Vector2.hpp"
#include "ecs/components/EntityComponent.h"
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
#endif// ENEMY_H