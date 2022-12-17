#include "RenderingSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/enemy/RndSpriteComponent.h"

RenderingSystem::RenderingSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{
}

void RenderingSystem::handleInput(sf::Event& event)
{
    //    sortSprites();
}

void RenderingSystem::sortSprites()
{
    mRegistry.sort<SpriteComponent>(
        [this](const SpriteComponent& lhs, const SpriteComponent& rhs)
        {
            auto lhsPos = lhs.mCurrentSprite.getPosition();
            auto rhsPos = rhs.mCurrentSprite.getPosition();

            if (lhs.mLayer == rhs.mLayer)
            {
                return lhsPos.y < rhsPos.y;
            }
            return lhs.mLayer < rhs.mLayer;
        });
}

void RenderingSystem::update(const sf::Time& dt)
{
}


void RenderingSystem::draw(sf::RenderWindow& window)
{
    mRegistry.view<SpriteComponent, ColliderComponent, HealthComponent>().each(
        [&](SpriteComponent& spriteComponent, ColliderComponent& colliderComponent,
            HealthComponent& healthComponent)
        {
            spriteComponent.draw(window);
            colliderComponent.draw(window);
            healthComponent.draw(window);
        });

    mRegistry.view<RndSpriteComponent, ColliderComponent, HealthComponent>().each(
        [&](RndSpriteComponent& rndSpriteComponent, ColliderComponent& colliderComponent,
            HealthComponent& healthComponent)
        {
            rndSpriteComponent.draw(window);
            colliderComponent.draw(window);
            healthComponent.draw(window);
        });
}
