#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H
#include "SFML/System/Vector2.hpp"
#include "ecs/components/enemy/AttackType.h"
#include <functional>
#include <string>
//
// enum class EntityState
//{
//    Idle,
//    Walking,
//    Jumping,
//    Attacking,
//    Hurt,
//    Dying
//};

struct EntityStatistic
{
    std::string mNameTag{};
    AttackType mAttackType{};
    float mAttackDamage{};
    float mAttackSpeed{};
    float mMovementSpeed{};
    int mHealth{};
    float mReactionTime{};

    std::function<void()> hit;

    int mDefense;
};

#endif// ENTITYCOMPONENT_H
