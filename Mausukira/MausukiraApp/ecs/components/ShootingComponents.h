#ifndef SHOOTINGCOMPONENTS_H
#define SHOOTINGCOMPONENTS_H

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"
#include "dungeon/CollisionBox.h"
#include <iostream>

struct ProjectileBody
{
    ProjectileBody()
    {
        mProjectile.setRadius(2);
        mProjectile.setFillColor(sf::Color::Cyan);
    }

    sf::CircleShape mProjectile;
};

struct WeaponComponent
{
    WeaponComponent()
    {
        mWeapon.setSize(sf::Vector2f{ 2, 4 });
        mWeapon.setFillColor(sf::Color::Blue);
    }

    sf::RectangleShape mWeapon;
    sf::Clock clock;
};

struct ProjectileCollider
{
    int id;
};

#endif// SHOOTINGCOMPONENTS_H
