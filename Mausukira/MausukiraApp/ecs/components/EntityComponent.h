#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H
#include <functional>
#include <string>

enum class EntityState
{
    Idle,
    Walking,
    Jumping,
    Attacking,
    Hurt,
    Dying
};

/** Just to differentiate between entities */
struct Player
{
};

struct Attack
{
    int minDamage;
    int maxDamage;
    std::function<void()> hit;
};

class EntityComponent
{
    std::string name;
    int maxHealth;
    int minHealth;

    Attack attack;
};

#endif// ENTITYCOMPONENT_H
