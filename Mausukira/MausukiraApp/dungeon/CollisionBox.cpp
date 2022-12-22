#include "CollisionBox.h"

sf::RectangleShape CollisionBox::setupCollider(const sf::FloatRect& rect, const CollisionType& type)
{
    if (type == CollisionType::FOOT)
    {
        return setupColliderForFoot(rect);
    }
    else
    {
        return setupColliderForBody(rect);
    }
}

sf::RectangleShape CollisionBox::setupColliderForFoot(const sf::FloatRect& rect)
{
    sf::RectangleShape rectangle;
    rectangle.setPosition(rect.left, rect.top);
    rectangle.setOrigin(FOOT_ORIGIN_X, FOOT_ORIGIN_Y);
    rectangle.setSize(sf::Vector2f(rect.width / 4, FOOT_SIZE_Y));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(1);
    return rectangle;
}

sf::RectangleShape CollisionBox::setupColliderForBody(const sf::FloatRect& rect)
{
    sf::RectangleShape rectangle;
    rectangle.setPosition(rect.left, rect.top);
    rectangle.setSize(sf::Vector2f(rect.width, rect.height));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(1);
    return rectangle;
}