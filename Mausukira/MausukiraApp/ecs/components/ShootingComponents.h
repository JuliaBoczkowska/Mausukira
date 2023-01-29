#ifndef SHOOTINGCOMPONENTS_H
#define SHOOTINGCOMPONENTS_H

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"
#include "dungeon/CollisionBox.h"
#include "entt/entity/entity.hpp"
#include <iostream>

struct ProjectileBody
{
    ProjectileBody(const int& size, sf::Color color = sf::Color::Cyan)
    {
        mProjectile.setRadius(size);
        mProjectile.setFillColor(color);
    }
    sf::CircleShape mProjectile;
};

enum class WeaponType
{
    MACHINE_GUN,
    PISTOL,
    SHOTGUN
};

struct ProjectileDamage
{
    float mDamage;
};

struct WeaponComponent
{
    WeaponComponent(const WeaponType& type)
    {
        mWeapon.setSize(sf::Vector2f{2, 4});
        mWeapon.setFillColor(sf::Color::Blue);
        this->type = type;
    }
    WeaponType type;
    sf::RectangleShape mWeapon;
    sf::Clock clock;
};

struct WeaponPlayer
{
    int id;
};

struct WeaponEnemy
{
    int id;
};

struct PlayerProjectileCollider
{
    entt::entity owner;
};

struct EnemyProjectileCollider
{
    entt::entity owner;
};

struct ProjectileCollider
{
    entt::entity owner;
};
#endif// SHOOTINGCOMPONENTS_H
