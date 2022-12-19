#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"
#include "scene/CollisionBox.h"
#include <iostream>

class Projectile
{
public:
    Projectile(const sf::Vector2f& playerCenter, const sf::Vector2f& aimDirectionNormalized);

    void update();
    void draw(sf::RenderWindow& window);

    float mMaxSpeed{5.f};

public:
    sf::CircleShape mProjectile;
    CollisionBox CollisionBox;
    sf::Vector2f mCurrVelocity{};
};


#endif// PROJECTILE_H
