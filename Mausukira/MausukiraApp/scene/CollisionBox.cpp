#include "CollisionBox.h"
#include <iostream>

CollisionBox::CollisionBox()
{
}

CollisionBox::CollisionBox(sf::FloatRect rect, COLLISION_TYPE type)
    : mCollisionBox(rect)
{
    setupRectangle(type);
}

void CollisionBox::setupRectangle(const COLLISION_TYPE& type)
{
    if (type == COLLISION_TYPE::FOOT)
    {
        setupRectForFoot();
    }
    else
    {
        setupRectForWholeObject();
    }
}
void CollisionBox::setupRectForFoot()
{
    auto newTop = mCollisionBox.top + mCollisionBox.width - 4;

    mCollisionBox =
        sf::FloatRect{mCollisionBox.left, newTop, mCollisionBox.width, mCollisionBox.height / 3};
    mRectangle.setPosition(mCollisionBox.left, mCollisionBox.top);
    mRectangle.setSize(sf::Vector2f(mCollisionBox.width, mCollisionBox.height));
    mRectangle.setFillColor(sf::Color::Transparent);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(1);
}

void CollisionBox::setupRectForWholeObject()
{
    mRectangle.setPosition(mCollisionBox.left, mCollisionBox.top);
    mRectangle.setSize(sf::Vector2f(mCollisionBox.width, mCollisionBox.height));
    mRectangle.setFillColor(sf::Color::Transparent);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(1);
}

void CollisionBox::draw(sf::RenderWindow& window)
{
    window.draw(mRectangle);
}

bool CollisionBox::intersects(CollisionBox& otherRom)
{

    if (mCollisionBox.contains(otherRom.mCollisionBox.left, otherRom.mCollisionBox.top))
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

void CollisionBox::updatePosition(sf::Vector2f position)
{
    updateCollider(position);
}

void CollisionBox::setup(sf::FloatRect rect)
{
    mCollisionBox = sf::FloatRect(rect);
    setupRectangle();
}

CollisionBox::CollisionBox(sf::FloatRect rect)
    : mCollisionBox(rect)
{
    setupRectangle();
}
void CollisionBox::updateCollider(sf::Vector2f position)
{
    mRectangle.move(position);
    mCollisionBox.left = mRectangle.getPosition().x;
    mCollisionBox.top = mRectangle.getPosition().y;
}

void CollisionBox::setInitialPosition(const sf::Vector2f& pos)
{
    mCollisionBox.left = pos.x;
    mCollisionBox.top = pos.y;
    setupRectForFoot();
}