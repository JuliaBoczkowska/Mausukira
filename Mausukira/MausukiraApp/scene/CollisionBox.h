#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class CollisionBox
{
public:
    enum class COLLISION_TYPE
    {
        FOOT,
        WHOLE
    };

    CollisionBox(sf::FloatRect rect, COLLISION_TYPE type);
    CollisionBox(sf::FloatRect rect);
    CollisionBox() = default;

    void setPosition(const sf::Vector2f& pos);
    void setupFromSpriteRect(sf::FloatRect rect);
    void moveCollisionBox(sf::Vector2f position);
    bool isColliding(CollisionBox& otherRom);
    void draw(sf::RenderWindow& window);

private:
    void setupCollider(sf::FloatRect& rect, const COLLISION_TYPE& type = COLLISION_TYPE::WHOLE);
    void setupColliderForGivenSurface(sf::FloatRect& rect);
    void setupColliderForFoot(sf::FloatRect& rect);


public:
    sf::RectangleShape mRectangle;
};


#endif// COLLISIONBOX_H
