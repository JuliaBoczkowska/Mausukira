#include "PlayerMoveSystem.h"
#include "dungeon/map/Constants.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/MovableComponent.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/VelocityComponent.h"
#include <iostream>

PlayerMoveSystem::PlayerMoveSystem(entt::registry& registry)
    : System(registry)
{
}

void PlayerMoveSystem::handleInput(sf::Event& event)
{
    sf::Vector2f velocity{0.f, 0.f};
    float speed = 100.f;
    Direction direction;

    handlePlayerBasicMovement(speed, velocity, direction);
    handlePlayerDash(event);
    velocity = preventHigherSpeedOnDiagonalMov(velocity);

    mRegistry.view<VelocityComponent, PlayerComponent>().each(
        [&](VelocityComponent& velocityComponent, PlayerComponent& playerComponent)
        {
            velocityComponent.mVelocity = velocity;
        });
}

void PlayerMoveSystem::handlePlayerDash(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::LShift)
        {
            dashTimer = DASH_DURATION;
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
    mRegistry.view<PlayerComponent, VelocityComponent, PositionComponent>().each(
        [&](PlayerComponent& playerComponent, VelocityComponent& velocityComponent,
            PositionComponent& positionComponent)
        {
            if (dashTimer > 0)
            {
                performDash(dt, velocityComponent, positionComponent);
            }
            else
            {
                positionComponent.mPosition += (velocityComponent.mVelocity * dt.asSeconds());
            }
        });
}

void PlayerMoveSystem::performDash(const sf::Time& dt, VelocityComponent& velocityComponent,
                                   PositionComponent& positionComponent)
{
    /** Calculate the percentage of the dash that has elapsed */
    float t = 1.0f - (dashTimer / DASH_DURATION);

    /** Use a smoothed easing function to smoothly decelerate the dash */
    float speed = DASH_SPEED * (1.0f - cos(t * PI)) / 2.0f;

    /** Update the player position based on the calculated speed */
    positionComponent.mPosition += (velocityComponent.mVelocity * speed * dt.asSeconds());

    /** Decrease the dash timer */
    dashTimer -= dt.asSeconds();
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
