//
// Created by Julchan on 27-Nov-22.
//

#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H

enum class EntityType
{
    Base,
    Enemy,
    Player
};

enum class EntityState
{
    Idle,
    Walking,
    Jumping,
    Attacking,
    Hurt,
    Dying
};

struct EntityComponent
{
    EntityState state{EntityState::Idle};
};

struct Player
{
};


#endif// ENTITYCOMPONENT_H
