#ifndef SHOTGUN_H
#define SHOTGUN_H


#include "Weapon.h"
class Shotgun : public Weapon
{

public:
    Shotgun(entt::registry& registry, sf::RenderWindow& window);
    void setupProjectile(const sf::Time& dt, entt::entity entity,
                         sf::Vector2f& weaponPosition) override;
};


#endif// SHOTGUN_H
