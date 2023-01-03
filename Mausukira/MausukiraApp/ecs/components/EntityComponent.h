#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H

#include "SFML/System/Vector2.hpp"
#include "AttackType.h"
#include <functional>
#include <string>

enum class MobState
{
    Idle,
    Walking,
    Attacking,
    Hurt,
    Died
};

struct EntityState
{
    MobState state{ MobState::Idle };
};

struct EntityStatistic
{
    std::string mNameTag{};
    AttackType mAttackType{};
    float mAttackDamage{};
    float mAttackSpeed{};
    float mMovementSpeed{};
    int mHealth{};
    float mReactionTime{};
    bool isTransitionToNextLevel{ false };
};

#endif// ENTITYCOMPONENT_H
