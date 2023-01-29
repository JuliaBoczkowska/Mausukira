#ifndef MACHINEGUN_H
#define MACHINEGUN_H
#include "Weapon.h"

class MachineGun : public Weapon
{
public:
    MachineGun(entt::registry& registry, sf::RenderWindow& window);
};


#endif// MACHINEGUN_H
