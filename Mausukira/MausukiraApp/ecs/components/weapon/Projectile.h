#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"
#include <iostream>

class Projectile
{
public:
    Projectile(const sf::Vector2f& playerCenter);

    void update();
    void draw(sf::RenderWindow& window) const;

private:
    sf::CircleShape mProjectile;
    sf::Vector2f mCurrVelocity{};
    float mMaxSpeed{10.f};
};


#endif// PROJECTILE_H
