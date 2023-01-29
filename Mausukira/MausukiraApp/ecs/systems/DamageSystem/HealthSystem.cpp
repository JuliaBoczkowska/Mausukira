#include "HealthSystem.h"
#include "ecs/components/AttachmentPoint.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/PlayerComponent.h"

HealthSystem::HealthSystem(entt::registry& registry)
    : System(registry)
{
}

void HealthSystem::takeDamage(HealthComponent& healthComponent, const int& damage)
{
    if (healthComponent.mCurrentHealth > 0)
    {
        healthComponent.mCurrentHealth = healthComponent.mCurrentHealth - damage;
        float percent = healthComponent.mCurrentHealth / healthComponent.mHealthMax;
        healthComponent.mHealthBarRect.setSize(sf::Vector2f{
            healthComponent.mHpBarWidth * percent, healthComponent.mHealthBarRect.getSize().y});
    }
}

bool HealthSystem::isDead(const int& mCurrentHealth)
{
    return mCurrentHealth <= 0;
}

void HealthSystem::whenHealthBelowZeroChangeEntityState()
{
    checkEnemyDeath();
    checkPlayerDeath();
}

void HealthSystem::checkPlayerDeath()
{
    auto view = mRegistry.view<PlayerComponent, HealthComponent>();
    for (auto& entity: view)
    {
        auto [player, health] = view.get(entity);

        if (isDead(health.mCurrentHealth))
        {
            player.isDead = true;
        }
    }
}

void HealthSystem::checkEnemyDeath()
{
    auto view = mRegistry.view<EntityState, HealthComponent, EntityStatistic>();
    for (auto& entity: view)
    {
        auto [entityState, health, entityStatistic] = view.get(entity);

        if (isDead(health.mCurrentHealth))
        {
            entityState.state = MobState::Died;
        }
    }
}

void HealthSystem::whenEnemyIsHitDoDamage()
{
    auto view = mRegistry.view<Relationship, EntityState, HealthComponent, EntityStatistic>();
    for (auto& entity: view)
    {
        auto [relationship, entityState, health, entityStatistic] = view.get(entity);
        auto* comp = mRegistry.try_get<Relationship>(entity);
        auto& curr = comp->first_child;
        auto& colliderComponent = mRegistry.get<ColliderComponent>(curr);

        if (colliderComponent.isHit)
        {
            takeDamage(health, 2);
            colliderComponent.isHit = false;
        }
    }
}


void HealthSystem::update(const sf::Time& dt)
{
    whenEnemyIsHitDoDamage();
    whenHealthBelowZeroChangeEntityState();

    auto view = mRegistry.view<PlayerComponent, HealthComponent>();
    for (auto& entity: view)
    {
        auto [player, health] = view.get(entity);
        auto* comp = mRegistry.try_get<Relationship>(entity);
        auto& curr = comp->first_child;
        auto& colliderComponent = mRegistry.get<ColliderComponent>(curr);

        if (colliderComponent.isHit)
        {
            takeDamage(health, colliderComponent.damageTaken);
            colliderComponent.isHit = false;
        }
    }
}
