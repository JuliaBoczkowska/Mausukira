#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "AttackType.h"
#include "VelocityComponent.h"
#include "ecs/components/PositionComponent.h"
#include "utils/RandomNumberGenerator.h"
#include <array>

struct AiComponent
{

    AiComponent()
    {
        double angle = generateFloatNumberInRange(0, 1) * 2 * PI;
        mWanderPoint = sf::Vector2f(2 * cos(angle), 2 * sin(angle));
    }

    /** Point used in wander behaviour calculations */
    sf::Vector2f mWanderPoint;

    /** Position of the player */
    PositionComponent* mPlayerPositionComponent;

    /** Velocity of the enemy */
    VelocityComponent* mVelocity;
};

struct SensorComponent
{
    SensorComponent()
    {
        mEnemyCircle.setRadius(4);
        mEnemyCircle.setFillColor(sf::Color::Cyan);
    }
    bool mIsPlayerInFieldOfView{false};
    sf::CircleShape mEnemyCircle;
    sf::Clock clock;
    float mTimePlayerWasLastSeen{};
    sf::Vector2f mLastSeenPosition;
    float fieldOfView{20};
    sf::VertexArray vertices;
    std::array<sf::Vector2f, 2> lineOfSight;
};
#endif// AICOMPONENT_H
