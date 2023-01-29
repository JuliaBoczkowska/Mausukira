#ifndef PISTOL_H
#define PISTOL_H
#include "Weapon.h"

class Pistol : public Weapon
{
public:
    Pistol(entt::registry& registry, sf::RenderWindow& window);
};


#endif// PISTOL_H
