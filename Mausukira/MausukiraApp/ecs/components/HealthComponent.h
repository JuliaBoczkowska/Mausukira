#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class HealthComponent
{
public:
    HealthComponent(float health);

    void setPosition(const sf::Vector2f& position);

    float mCurrentHealth{ 0.f };
    float mHealthMax{ 0.f };
    float mHpBarWidth{ 16.f };
    sf::RectangleShape mHealthBarRect;
    sf::RectangleShape mHealthBarOutline;
};

#endif// HEALTHCOMPONENT_H
