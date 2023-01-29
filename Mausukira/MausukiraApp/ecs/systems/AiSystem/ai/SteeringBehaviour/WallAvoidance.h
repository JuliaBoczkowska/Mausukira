#ifndef WALLAVOIDANCE_H
#define WALLAVOIDANCE_H
#include "SteeringBehaviourBase.h"

/** Returns a force that keeps the agent away from wall */
class WallAvoidance : public SteeringBehaviourBase
{
public:
    explicit WallAvoidance(entt::registry& registry, std::vector<sf::RectangleShape*>& collisions);
    sf::Vector2f getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                  PositionComponent& positionComponent,
                                  SteeringBehaviourComponent& steeringBehaviourComponent) override;

private:
    void adjustWanderPoint(AiComponent& aiComponent, PositionComponent& positionComponent,
                           SteeringBehaviourComponent& steeringBehaviourComponent,
                           const sf::Vector2f& force) const;
    bool compareIntersectionPoints(const sf::Vector2f& position,
                                   const sf::Vector2f& intersectionPoint,
                                   sf::Vector2f& closestIntersectionPoint, int& wallID,
                                   int& wallIter) const;
    std::array<sf::Vector2f, 3> createWhiskers(
        const PositionComponent& positionComponent,
        SteeringBehaviourComponent& steeringBehaviourComponent) const;
    sf::Vector2f getPoint(sf::RectangleShape* const& collider, int i) const;


    std::vector<sf::RectangleShape*>& mCollisions;
    const float mWhiskerLength = 32.f;
    /** Radius of the circle in front of enemy*/
    const float mWanderRadius{50};
    const float mWanderCircleProjectDistance{2};
};

#endif// WALLAVOIDANCE_H
