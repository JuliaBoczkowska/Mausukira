#include "PlayerMoveSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/MovableComponent.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/TransformComponent.h"

PlayerMoveSystem::PlayerMoveSystem(entt::registry& registry)
    : System(registry)
{
}

#include <iostream>
void PlayerMoveSystem::handleInput(sf::Event& event)
{
    sf::Vector2f velocity{0.f, 0.f};
    float speed = 100.f;
    Direction direction;

    handlePlayerBasicMovement(speed, velocity, direction);
    handlePlayerDash(event);
    velocity = preventHigherSpeedOnDiagonalMov(velocity);

    mRegistry.view<MovableComponent, ColliderComponent, TransformComponent, PlayerComponent>().each(
        [&](MovableComponent& movableComponent, ColliderComponent& colliderComponent,
            TransformComponent& transformComponent, PlayerComponent& playerComponent)
        {
            transformComponent.mVelocity = velocity;
            movableComponent.mDirection = direction;
        });
}

void PlayerMoveSystem::handlePlayerDash(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::LShift)
        {
            mDashSpeed = 20.f;
        }
    }
}

void PlayerMoveSystem::handlePlayerBasicMovement(float speed, sf::Vector2f& velocity,
                                                 Direction& direction) const
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;
        direction = Direction::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
        direction = Direction::RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity.y -= speed;
        direction = Direction::TOP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y += speed;
        direction = Direction::DOWN;
    }
}

void PlayerMoveSystem::update(const sf::Time& dt)
{
    mRegistry.view<MovableComponent, ColliderComponent, TransformComponent>().each(
        [&](MovableComponent& movableComponent, ColliderComponent& colliderComponent,
            TransformComponent& transformComponent)
        {
            transformComponent.moveBy(transformComponent.mVelocity * mDashSpeed * dt.asSeconds());
        });
    mDashSpeed = 1.f;
}

sf::Vector2f& PlayerMoveSystem::preventHigherSpeedOnDiagonalMov(sf::Vector2f& velocity) const
{
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        /** When player is moving diagonally it will move faster,
         * thus I need to divide both directions by root 2. */
        velocity /= sqrt(2.f);
    }
    return velocity;
}
