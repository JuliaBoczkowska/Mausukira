#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class HealthComponent
{
public:
    HealthComponent(float health);
    void updateHealth(const float& damage);
    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void moveBy(const sf::Vector2f& mov);

private:
    float mCurrentHealth{0};
    float mHealthMax{0};
    float mHpBarWidth{16.f};
    sf::RectangleShape mHealthBarRect;
    sf::RectangleShape mHealthBarOutline;
};


#endif// HEALTHCOMPONENT_H
