#include "Pistol.h"

Pistol::Pistol(entt::registry& registry, sf::RenderWindow& window)
    : Weapon(registry, window)
{
    mWeaponDamage = 10;
    mWeaponDelay = 400;
    mProjectileSize = 3;
    mAttackSpeed = 1;
    mProjectileColor = sf::Color::Yellow;
}
