#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H

#include "AttackType.h"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include <functional>
#include <string>

enum class MobState
{
    Idle,
    Attacking,
    Died
};

struct EntityState
{
    MobState state{MobState::Idle};
};

struct EntityStatistic
{
    AttackType mAttackType{};
    float mAttackDamage{};
    float mAttackSpeed{};
    float mMovementSpeed{};
    int mHealth{};
    float mReactionTime{};
    float mDecelerationSpeed{};
    float mActiveWanderTime{};
    float mRestTime{};
    bool isSelectedAsTransitionToNextLevel{false};
};

struct EnemyDamage
{
    float mAttackDamage{};
    float mAttackSpeed{};
    float mTimeProjectileShot{};
    sf::Clock clock;
    sf::Clock shootingClock{};
};

#endif// ENTITYCOMPONENT_H
