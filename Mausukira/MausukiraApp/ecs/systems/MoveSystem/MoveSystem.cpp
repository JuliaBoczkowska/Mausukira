#include "MoveSystem.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/PositionComponent.h"

MoveSystem::MoveSystem(entt::registry& registry)
    : System(registry)
    , mPlayerMoveSystem(registry)
{
    mRegistry.view<SpriteComponent, ColliderComponent, HealthComponent, PositionComponent>().each(
        [&](SpriteComponent& spriteComponent, ColliderComponent& colliderComponent,
            HealthComponent& healthComponent, PositionComponent& positionComponent)
        {
            const auto& position = positionComponent.mPosition;
            colliderComponent.mRectangle.setPosition(position);
            for (auto& sprite: spriteComponent.mSprites)
            {
                sprite.setPosition(position);
            }
            healthComponent.setPosition(position);
        });
}

void MoveSystem::handleInput(sf::Event& event)
{
    mPlayerMoveSystem.handleInput(event);
}

void MoveSystem::update(const sf::Time& dt)
{
    mPlayerMoveSystem.update(dt);
}

void MoveSystem::postUpdate()
{
    mRegistry.view<SpriteComponent, ColliderComponent, HealthComponent, PositionComponent>().each(
        [&](SpriteComponent& spriteComponent, ColliderComponent& colliderComponent,
            HealthComponent& healthComponent, PositionComponent& positionComponent)
        {
            const auto& position = positionComponent.mPosition;
            colliderComponent.mRectangle.setPosition(position);
            healthComponent.setPosition(position);
            for (auto& sprite: spriteComponent.mSprites)
            {
                sprite.setPosition(position);
            }
        });
}
