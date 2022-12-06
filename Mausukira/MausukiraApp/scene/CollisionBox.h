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
    CollisionBox();

    void setupRectangle(const COLLISION_TYPE& type = COLLISION_TYPE::WHOLE);
    void setupRectForWholeObject();
    void setupRectForFoot();
    void setup(sf::FloatRect rect);
    void setInitialPosition(const sf::Vector2f& pos);

    bool intersects(CollisionBox& otherRom);
    void updateCollider(sf::Vector2f position);
    void updatePosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window);


private:
    sf::RectangleShape mRectangle;
    sf::FloatRect mCollisionBox;
};


#endif// COLLISIONBOX_H
