#ifndef STEERINGBEHAVIOUR_H
#define STEERINGBEHAVIOUR_H


#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "dungeon/map/Constants.h"
#include "ecs/components/SteeringBehaviourComponent.h"
#include <list>
#include <memory>
#include <optional>

class MapContext;
class Tile;
class PositionComponent;
class ColliderComponent;
class AiComponent;
class SteeringBehaviour
{
    const float mWhiskerLength = 50.f;
    const float mWallAvoidanceWeight = 10.0;
    const float mWanderWeight = 1.0;
    const float mSeekWeight = 0.5;
    const float mArriveWeight = 1.0;

public:
    SteeringBehaviour(MapContext& tileMap);

    /** Calculate the steering force */
    sf::Vector2f getSteeringForce(AiComponent& aiComponent, PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent);

private:
    /** Seeks a target which in my case is a player */
    sf::Vector2f seek(const AiComponent& aiComponent, const PositionComponent& positionComponent,
                      SteeringBehaviourComponent& steeringBehaviourComponent);

    /** Seeks a target which in my case is a player
     * and arrives at its position with 0 velocity
     * The arriving is done with a decelaration of the velocity*/
    sf::Vector2f arrive(const AiComponent& aiComponent, const PositionComponent& positionComponent,
                        SteeringBehaviourComponent& steeringBehaviourComponent);

    /** Agent wanders around the map randomly until it sees player */
    sf::Vector2f wander(AiComponent& aiComponent, PositionComponent& positionComponent,
                        SteeringBehaviourComponent& steeringBehaviourComponent);

    /** Separate enemies from each other*/
    sf::Vector2f separate(const std::list<ColliderComponent*>& agents);

    /** Returns a force that keeps the agent away from wall*/
    sf::Vector2f avoidWalls(AiComponent& aiComponent, PositionComponent& positionComponent,
                            SteeringBehaviourComponent& steeringBehaviourComponent);

    std::array<sf::Vector2f, 3> createWhiskers(
        const PositionComponent& positionComponent,
        SteeringBehaviourComponent& steeringBehaviourComponent) const;

    sf::Vector2f getPoint(sf::RectangleShape* const& collider, int i) const;

    bool compareIntersectionPoints(const sf::Vector2f& position,
                                   const sf::Vector2f& intersectionPoint,
                                   sf::Vector2f& closestIntersectionPoint, int& wallID,
                                   int& wallIter) const;

    bool accumulateForces(sf::Vector2f& totalForce, sf::Vector2f forceToAdd, float maxForce);


    /** Checks if the character is within the radius. */
    float mArriveRadius{2};

    /** Enemy slows down as it is close to player */
    float mArriveTimeToTarget{0.25f};

    /** Radius of the circle in front of enemy*/
    float mWanderRadius{50};

    /** The distance of the circle projection */
    float mMaxAmountOfRandomDisplacement{2};
    float mWanderCircleProjectDistance{2};
    MapContext& mTileMap;
    std::vector<sf::RectangleShape*> collisions;
};


#endif// STEERINGBEHAVIOUR_H
