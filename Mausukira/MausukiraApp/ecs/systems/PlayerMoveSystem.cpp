#include "PlayerMoveSystem.h"
#include "../components/MovableComponent.h"
#include "../components/SpriteComponent.h"
#include "ecs/components/ColliderComponent.h"

PlayerMoveSystem::PlayerMoveSystem(entt::registry& registry)
    : System(registry)
{
}

void PlayerMoveSystem::handleInput(sf::Event& event)
{
}

void PlayerMoveSystem::update(const sf::Time& dt)
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

    mRegistry.view<MovableComponent, SpriteComponent, ColliderComponent, TransformComponent>().each(
        [&](MovableComponent& movableComponent, SpriteComponent& spriteComponent,
            ColliderComponent& colliderComponent, TransformComponent& transformComponent)
        {
            if (colliderComponent.mIsColliding)
            {
                transformComponent.setPosition(transformComponent.mPositionOld);
                velocity = sf::Vector2f{0.f, 0.f};
            }
            else
            {
                spriteComponent.moveBy(velocity * dt.asSeconds());
                movableComponent.mDirection = direction;
            }
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
