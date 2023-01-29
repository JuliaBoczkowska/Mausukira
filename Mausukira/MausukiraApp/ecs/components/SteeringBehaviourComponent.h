#ifndef STEERINGBEHAVIOURCOMPONENT_H
#define STEERINGBEHAVIOURCOMPONENT_H
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include <array>

enum EnemyBehaviour
{
    NA = 0,
    REST = 1 << 1,
    ARRIVE = 1 << 2,
    WANDER = 1 << 3,
    WALL_AVOIDANCE = 1 << 4,
    SEPARATION = 1 << 5,
    FLEE = 1 << 6,
};

bool isFlagOn(int& mBehaviourFlag, EnemyBehaviour enemyBehaviourFlag);
void setFlagOn(int& mBehaviourFlag, EnemyBehaviour behaviourType);
void clearFlag(int& mBehaviourFlag);

/** Values that will be used for steering behaviour*/
struct SteeringBehaviourComponent
{
    /** The speed at which the entity can rotate */
    float deceleration{10.f};
    float mActiveWanderTime{};
    float mRestTime{};

    /** Mass of the entity */
    float mMass{1};

    /** Max force of the enemy entity */
    float mMaxForce{2};

    /** Max speed of the enemy entity */
    float maxSpeed{1.5};

    /** How far the enemy can see */
    bool isInCloseDistanceWithOtherEnemy{false};

    /** The direction vector*/
    sf::Vector2f mDirectionVector;

    /** A vector orthogonal to directionVector */
    sf::Vector2f mSideVectorToDirection;

    float restPointInTime{};

    sf::Clock clock;
    sf::Vector2f newPoint{};
    std::pair<sf::Vector2f, sf::Vector2f> normal;
    std::array<sf::Vector2f, 3> whiskers;
    int mBehaviourFlag;
};

#endif// STEERINGBEHAVIOURCOMPONENT_H
