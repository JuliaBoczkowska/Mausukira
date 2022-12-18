#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& playerCenter, const sf::Vector2f& aimDirectionNormalized)
{
    mCurrVelocity = aimDirectionNormalized * mMaxSpeed;
    mProjectile.setRadius(2);
    mProjectile.setFillColor(sf::Color::Cyan);
    mProjectile.setPosition(playerCenter);
}
void Projectile::update()
{
    mProjectile.move(mCurrVelocity);
}

void Projectile::draw(sf::RenderWindow& window) const
{
    window.draw(mProjectile);
}
