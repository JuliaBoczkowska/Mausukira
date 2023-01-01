#include <iostream>
#include "PlayerMoveSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/MovableComponent.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/components/PositionComponent.h"
#include "dungeon/map/Tile/TileHelper.h"

PlayerMoveSystem::PlayerMoveSystem(entt::registry& registry)
    : System(registry)
{
}

void PlayerMoveSystem::handleInput(sf::Event& event)
{
    sf::Vector2f velocity{ 0.f, 0.f };
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
    mRegistry.view<VelocityComponent, PositionComponent>().each(
        [&](VelocityComponent& velocityComponent,
            PositionComponent& positionComponent)
        {
            positionComponent.mPosition += (velocityComponent.mVelocity * mDashSpeed * dt.asSeconds());
//            auto [x, y] = tile_helper::worldCoordinateToTileCoordinate(positionComponent.mPosition.x,
//                positionComponent.mPosition.y);
//            std::cout << x << " " << y << std::endl;
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
