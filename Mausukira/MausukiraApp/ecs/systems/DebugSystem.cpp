#include "DebugSystem.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/weapon/Weapon.h"
#include <iostream>

DebugSystem::DebugSystem(entt::registry& registry)
    : System(registry)
{
}
void DebugSystem::update(const sf::Time& dt)
{
    if (doOnce)
    {
        mRegistry.view<EntityStatistic>().each(
            [&](EntityStatistic& entityStatistic)
            {
                std::cout << std::endl;
                std::string temp;
                std::cout << "Name: " << entityStatistic.mNameTag << std::endl;
                std::cout << "Health: " << entityStatistic.mHealth << std::endl;
                std::cout << "MovementSpeed: " << entityStatistic.mMovementSpeed << std::endl;
                if (entityStatistic.mAttackType == AttackType::Melee)
                {
                    temp = "Melee";
                }
                else
                {
                    temp = "Ranged";
                }
                std::cout << "ReactionTime: " << entityStatistic.mReactionTime << std::endl;
                std::cout << "AttackType: " << temp << std::endl;
                std::cout << "AttackSpeed: " << entityStatistic.mAttackSpeed << std::endl;
                std::cout << "AttackDamage: " << entityStatistic.mAttackDamage << std::endl;
            });
        doOnce = false;
    }
}
