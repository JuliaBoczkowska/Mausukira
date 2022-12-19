#include "CollisionBox.h"

CollisionBox::CollisionBox(sf::FloatRect rect)
{
    setupCollider(rect);
}

CollisionBox::CollisionBox(sf::FloatRect rect, CollisionType collisionType)

{
    setupCollider(rect, collisionType);
}

void CollisionBox::setupCollider(sf::FloatRect& rect, const CollisionType& type)
{
    if (type == CollisionType::FOOT)
    {
        setupColliderForFoot(rect);
    }
    else
    {
        setupColliderForGivenSurface(rect);
    }
}
void CollisionBox::setupColliderForFoot(sf::FloatRect& rect)
{
    mRectangle.setPosition(rect.left, rect.top);
    mRectangle.setOrigin(FOOT_ORIGIN_X, FOOT_ORIGIN_Y);
    mRectangle.setSize(sf::Vector2f(rect.width / 4, FOOT_SIZE_Y));
    mRectangle.setFillColor(sf::Color::Transparent);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(1);
}

void CollisionBox::setupColliderForGivenSurface(sf::FloatRect& rect)
{
    mRectangle.setPosition(rect.left, rect.top);
    mRectangle.setSize(sf::Vector2f(rect.width, rect.height));
    mRectangle.setFillColor(sf::Color::Transparent);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(1);
}

void CollisionBox::draw(sf::RenderWindow& window)
{
    window.draw(mRectangle);
}

bool CollisionBox::isColliding(CollisionBox& otherRom)
{
    sf::FloatRect otherCollisionBox2{otherRom.mRectangle.getGlobalBounds()};
    sf::FloatRect myCollisionBox{mRectangle.getGlobalBounds()};

    if (otherCollisionBox2.intersects(myCollisionBox))
    {
        mRectangle.setFillColor(sf::Color::Green);
        return true;
    }
    else
    {
        mRectangle.setFillColor(sf::Color::Transparent);
    }
    return false;
}

void CollisionBox::moveCollisionBox(sf::Vector2f position)
{
    mRectangle.move(position);
}

void CollisionBox::setupFromSpriteRect(sf::FloatRect rect)
{
    setupCollider(rect);
}

void CollisionBox::setPosition(const sf::Vector2f& pos)
{
    mRectangle.setPosition(pos);
}