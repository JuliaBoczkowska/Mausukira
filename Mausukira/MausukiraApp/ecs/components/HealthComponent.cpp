#include "HealthComponent.h"

HealthComponent::HealthComponent(float health)
    : mCurrentHealth(health)
    , mHealthMax(health)
{
    mHealthBarRect.setFillColor(sf::Color::Red);
    mHealthBarRect.setSize(sf::Vector2f(mHpBarWidth, 2.f));

    mHealthBarOutline.setSize(sf::Vector2f(mHpBarWidth, 2.f));
    mHealthBarOutline.setFillColor(sf::Color::Transparent);
    mHealthBarOutline.setOutlineColor(sf::Color::Black);
    mHealthBarOutline.setOutlineThickness(1);
}

void HealthComponent::setPosition(const sf::Vector2f& position)
{
    sf::Vector2f headPosition{ 32 / 4, 0 };
    mHealthBarRect.setPosition(position + headPosition);
    mHealthBarOutline.setPosition(position + headPosition);
}