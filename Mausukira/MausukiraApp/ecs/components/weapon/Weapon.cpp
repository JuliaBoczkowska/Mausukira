#include "Weapon.h"

Weapon::Weapon(sf::RenderWindow& renderWindow)
    : mRenderWindow(renderWindow)
{
}

Weapon::Weapon(const Weapon& c)
    : mRenderWindow(c.mRenderWindow)
{
}

Weapon::Weapon(Weapon&& c) noexcept
    : Weapon(c.mRenderWindow)
{
}


void Weapon::draw(sf::RenderWindow& window)
{
    for (const auto& projectile: mProjectiles)
    {
        projectile->draw(window);
    }
}

void Weapon::update(const sf::Time& deltaTime)
{
    for (const auto& projectile: mProjectiles)
    {
        projectile->update();
    }
}

Weapon& Weapon::operator=(Weapon&& other)
{
    return *this;
}

void Weapon::shoot(const sf::Vector2f& playerCenter, const sf::Vector2f& mAimDirectionNormalized)
{
    auto projectile = std::make_unique<Projectile>(mRenderWindow, playerCenter);
    projectile->mCurrVelocity = mAimDirectionNormalized * projectile->mMaxSpeed;
    mProjectiles.emplace_back(std::move(projectile));
}
