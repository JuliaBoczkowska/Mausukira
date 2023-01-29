#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include "ecs/components/ShootingComponents.h"
#include "ecs/systems/System.h"

class HealthComponent;

class HealthSystem : public System
{
public:
    explicit HealthSystem(entt::registry& registry);

    void update(const sf::Time& dt) override;

private:
    void takeDamage(HealthComponent& healthComponent, const int& damage);

    void whenEnemyIsHitDoDamage();

    void whenHealthBelowZeroChangeEntityState();

    bool isDead(const int& mCurrentHealth);
    void checkEnemyDeath();
    void checkPlayerDeath();
    
private:
    WeaponComponent* mWeaponComponent;
};


#endif// HEALTHSYSTEM_H
