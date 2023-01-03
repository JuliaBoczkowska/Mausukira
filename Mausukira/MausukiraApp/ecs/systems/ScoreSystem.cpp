#include "ScoreSystem.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/ScoreComponent.h"

ScoreSystem::ScoreSystem(entt::registry& registry)
    : System(registry)
{
}


void ScoreSystem::update(const sf::Time& dt)
{
    int tempScore = 0;
    mRegistry.view<EntityState, HealthComponent>().each(
        [&](auto entity, EntityState& entityStatistic, HealthComponent& healthComponent)
        {
            if (entityStatistic.state == MobState::Died)
            {
                tempScore += 10;
            }
        });

    mRegistry.view<ScoreComponent>().each(
        [&](ScoreComponent& scoreComponent)
        {
            scoreComponent.score += tempScore;
            scoreComponent.counter.setString("Score: " + std::to_string(scoreComponent.score));
        });
}