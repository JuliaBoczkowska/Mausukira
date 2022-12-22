#include "Weapon.h"

Weapon::Weapon(sf::RenderWindow* renderWindow)
    : mRenderWindow(renderWindow)
{
    clock.restart();
}


Weapon::Weapon(Weapon&& c) noexcept
    : Weapon(c.mRenderWindow)
{
    mProjectiles = std::move(c.mProjectiles);
}

Weapon::Weapon(const Weapon& c)
    : Weapon(c.mRenderWindow)
{
    mProjectiles = std::move(c.mProjectiles);
}

Weapon& Weapon::operator=(Weapon&& other)
{
    mRenderWindow = other.mRenderWindow;
    mProjectiles = std::move(other.mProjectiles);
    return *this;
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
    updateProjectilesPosition();
}

void Weapon::updateProjectilesPosition()
{
    for (const auto& projectile: mProjectiles)
    {
        projectile->update();
    }
}

void Weapon::shoot(const sf::Vector2f& playerCenter, const sf::Vector2f& mAimDirectionNormalized)
{
    if (clock.getElapsedTime().asMilliseconds() > 300)
    {
        clock.restart();
        auto projectile = new Projectile(playerCenter, mAimDirectionNormalized);
        mProjectiles.emplace_back(std::move(projectile));
    }
}
