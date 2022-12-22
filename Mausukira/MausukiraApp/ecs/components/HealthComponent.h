#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class HealthComponent
{
public:
    HealthComponent(float health);

    void setPosition(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);

    bool isDead();

    float mCurrentHealth{ 0 };
    float mHealthMax{ 0 };
    float mHpBarWidth{ 16.f };
    sf::RectangleShape mHealthBarRect;
    sf::RectangleShape mHealthBarOutline;
};


#endif// HEALTHCOMPONENT_H
