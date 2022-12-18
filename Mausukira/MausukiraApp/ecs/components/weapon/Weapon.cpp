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
    updateProjectilesPosition();
    deleteProjectilesOutsideWindow();
}

void Weapon::updateProjectilesPosition()
{
    for (const auto& projectile: mProjectiles)
    {
        projectile->update();
    }
}


void Weapon::deleteProjectilesOutsideWindow()
{
    for (int i = 0; i < mProjectiles.size(); i++)
    {
        auto projectile = mProjectiles[i]->mProjectile.getPosition();
        const auto& viewSize = mRenderWindow.getDefaultView().getSize();
        if (projectile.x < 0 || projectile.x > viewSize.x || projectile.y > viewSize.y ||
            projectile.y < 0)
        {
            mProjectiles.erase(mProjectiles.begin() + i);
        }
    }
}

Weapon& Weapon::operator=(Weapon&& other)
{
    return *this;
}

void Weapon::shoot(const sf::Vector2f& playerCenter, const sf::Vector2f& mAimDirectionNormalized)
{
    auto projectile = std::make_unique<Projectile>(playerCenter, mAimDirectionNormalized);
    mProjectiles.emplace_back(std::move(projectile));
}
