#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class CollisionBox
{
public:
    enum class CollisionType
    {
        FOOT,
        BODY,
        PROJECTILE,
        ENEMY,
        HERO
    };

    static constexpr int FOOT_ORIGIN_X = -12;
    static constexpr int FOOT_ORIGIN_Y = -28;
    static constexpr int FOOT_SIZE_Y = 3;

    CollisionBox() = default;

    static sf::RectangleShape setupCollider(const sf::FloatRect& rect, const CollisionType& type = CollisionType::BODY);

private:
    static sf::RectangleShape setupColliderForBody(const sf::FloatRect& rect);

    static sf::RectangleShape setupColliderForFoot(const sf::FloatRect& rect);

    sf::RectangleShape mRectangle;
};


#endif// COLLISIONBOX_H
