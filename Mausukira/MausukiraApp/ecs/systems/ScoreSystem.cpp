#include "ScoreSystem.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/ScoreComponent.h"

ScoreSystem::ScoreSystem(entt::registry& registry)
    : System(registry)
{
}

void ScoreSystem::handleInput(sf::Event& event)
{
}

#include <iostream>

void ScoreSystem::update(const sf::Time& dt)
{
    int tempScore = 0;
    mRegistry.view<EntityStatistic, HealthComponent>().each(
        [&](auto entity, EntityStatistic& entityStatistic, HealthComponent& healthComponent)
        {
            if (healthComponent.isDead())
            {
                mRegistry.remove<HealthComponent>(entity);
                tempScore += 10;
            }
        });


    if (tempScore != 0)
    {
        mRegistry.view<ScoreComponent>().each(
            [&](ScoreComponent& scoreComponent)
            {
                scoreComponent.score += tempScore;
                std::cout << scoreComponent.score << std::endl;
            });
    }
}