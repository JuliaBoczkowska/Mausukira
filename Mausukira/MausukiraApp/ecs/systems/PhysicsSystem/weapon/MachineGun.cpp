#include "MachineGun.h"

MachineGun::MachineGun(entt::registry& registry, sf::RenderWindow& window)
    : Weapon(registry, window)
{
    mWeaponDamage = 8;
    mWeaponDelay = 100;
    mAttackSpeed = 3;
    mProjectileColor = sf::Color::Blue;
    mProjectileSize = 1;
}
