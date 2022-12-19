#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& playerCenter, const sf::Vector2f& aimDirectionNormalized)
{
    mCurrVelocity = aimDirectionNormalized * mMaxSpeed;
    mProjectile.setRadius(2);
    mProjectile.setFillColor(sf::Color::Cyan);
    mProjectile.setPosition(playerCenter);
    CollisionBox.setupFromSpriteRect(mProjectile.getGlobalBounds());
}

void Projectile::update()
{
    mProjectile.move(mCurrVelocity);
    CollisionBox.moveCollisionBox(mCurrVelocity);
}

void Projectile::draw(sf::RenderWindow& window)
{
    window.draw(mProjectile);
    CollisionBox.draw(window);
}