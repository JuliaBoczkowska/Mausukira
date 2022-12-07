#include "PlayerMoveSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/MovableComponent.h"
#include "ecs/components/TransformComponent.h"

PlayerMoveSystem::PlayerMoveSystem(entt::registry& registry)
    : System(registry)
{
}

void PlayerMoveSystem::handleInput(sf::Event& event)
{
    sf::Vector2f velocity{0.f, 0.f};
    float speed = 100.f;
    Direction direction;

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

    velocity = preventHigherSpeedOnDiagonalMov(velocity);
    mRegistry.view<MovableComponent, ColliderComponent, TransformComponent>().each(
        [&](MovableComponent& movableComponent, ColliderComponent& colliderComponent,
            TransformComponent& transformComponent)
        {
            transformComponent.mVelocity = velocity;
            movableComponent.mDirection = direction;
        });
}
#include <iostream>
void PlayerMoveSystem::update(const sf::Time& dt)
{
    mRegistry.view<MovableComponent, ColliderComponent, TransformComponent>().each(
        [&](MovableComponent& movableComponent, ColliderComponent& colliderComponent,
            TransformComponent& transformComponent)
        {
            auto dupchan = dt.asSeconds();
            auto dupiarz = transformComponent.mVelocity * dupchan;
            transformComponent.moveBy(dupiarz);
        });
}
sf::Vector2f& PlayerMoveSystem::preventHigherSpeedOnDiagonalMov(sf::Vector2f& velocity) const
{
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        /** When you're moving diagonally you need
         * to think in triangles and of the Pythagoras theorem
         * - you'll want to compensate by dividing both directions by root 2. */
        velocity /= sqrt(2.f);
    }
    return velocity;
}
