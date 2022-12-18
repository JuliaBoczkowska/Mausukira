#ifndef WEAPON_H
#define WEAPON_H
#include "Projectile.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window.hpp"
#include "states_stack/SharedContext.h"

class Weapon
{
public:
    Weapon(sf::RenderWindow& renderWindow);
    Weapon(const Weapon&);
    Weapon(Weapon&& c) noexcept;
    Weapon& operator=(Weapon&& other);

    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
    void shoot(const sf::Vector2f& playerCenter, const sf::Vector2f& mAimDirectionNormalized);

private:
    sf::RenderWindow& mRenderWindow;
    std::vector<std::unique_ptr<Projectile>> mProjectiles;
    void deleteProjectilesOutsideWindow();
    void updateProjectilesPosition();
};
#endif// WEAPON_H
