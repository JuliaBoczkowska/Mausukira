#include "EnemyStateSystem.h"
#include "ecs/components/EntityComponent.h"

EnemyStateSystem::EnemyStateSystem(entt::registry& registry)
    : System(registry)
    , mAttackStateSystem(registry)
    , mIdleStateSystem(registry)
{
}
void EnemyStateSystem::update(const sf::Time& dt)
{
    mRegistry.view<EntityState>().each(
        [&](EntityState& entityState)
        {
            switch (entityState.state)
            {
                case MobState::Idle: mIdleStateSystem.update(dt); break;
                case MobState::Attacking: mAttackStateSystem.update(dt); break;
                case MobState::Died: break;
            }
        });
}
