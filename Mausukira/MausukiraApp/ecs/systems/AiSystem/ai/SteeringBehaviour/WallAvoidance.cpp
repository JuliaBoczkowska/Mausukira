#include "WallAvoidance.h"

WallAvoidance::WallAvoidance(entt::registry& registry, std::vector<sf::RectangleShape*>& collisions)
    : SteeringBehaviourBase(registry)
    , mCollisions(collisions)
{
}

void WallAvoidance::adjustWanderPoint(AiComponent& aiComponent,
                                      PositionComponent& positionComponent,
                                      SteeringBehaviourComponent& steeringBehaviourComponent,
                                      const sf::Vector2f& force) const
{
    aiComponent.mWanderPoint = force;
    auto rnd1 = generateFloatNumberInRange(-1, 1);
    auto rnd2 = generateFloatNumberInRange(-1, 1);
    sf::Vector2f temp(rnd1, rnd2);
    aiComponent.mWanderPoint += temp * 10.f;
    /** Make a unit vector */
    aiComponent.mWanderPoint = normalizeVector(aiComponent.mWanderPoint);

    /** Make the length of the vector the same as radius */
    aiComponent.mWanderPoint *= mWanderRadius;

    sf::Vector2f targetLocal =
        aiComponent.mWanderPoint + sf::Vector2f{mWanderCircleProjectDistance, 0};

    sf::Vector2f pointWorldSpace = localSpaceToWorldSpace(
        targetLocal, steeringBehaviourComponent.mDirectionVector,
        steeringBehaviourComponent.mSideVectorToDirection, positionComponent.mPosition);

    steeringBehaviourComponent.newPoint = pointWorldSpace;
}

bool WallAvoidance::compareIntersectionPoints(const sf::Vector2f& position,
                                              const sf::Vector2f& intersectionPoint,
                                              sf::Vector2f& closestIntersectionPoint, int& wallID,
                                              int& wallIter) const
{
    if (calculateVectorsLength(position, intersectionPoint) <
        calculateVectorsLength(position, closestIntersectionPoint))
    {
        closestIntersectionPoint = intersectionPoint;
        wallID = wallIter;
        return true;
    }
    return false;
}

std::array<sf::Vector2f, 3> WallAvoidance::createWhiskers(
    const PositionComponent& positionComponent,
    SteeringBehaviourComponent& steeringBehaviourComponent) const
{
    std::array<sf::Vector2f, 3> whiskers;
    auto position = positionComponent.mPosition;

    auto positionAlignedToEnemyCenter = sf::Vector2f{position.x + 16, position.y + 16};
    auto heading = steeringBehaviourComponent.mDirectionVector;

    sf::Vector2f centralRay = positionAlignedToEnemyCenter + mWhiskerLength * heading;

    auto rotatedHeading = rotateBy(15, heading);
    sf::Vector2f leftWhisker = positionAlignedToEnemyCenter + mWhiskerLength / 2 * rotatedHeading;

    rotatedHeading = rotateBy(-15, heading);
    sf::Vector2f rightWhisker = positionAlignedToEnemyCenter + mWhiskerLength / 2 * rotatedHeading;

    whiskers.at(0) = leftWhisker;
    whiskers.at(1) = centralRay;
    whiskers.at(2) = rightWhisker;

    /** In order to be drawn they need to be stored in each enemy */
    steeringBehaviourComponent.whiskers = whiskers;
    return whiskers;
}

sf::Vector2f WallAvoidance::getPoint(sf::RectangleShape* const& collider, int i) const
{
    sf::Transform matrix = collider->getTransform();
    return matrix.transformPoint(collider->getPoint(i));
}

sf::Vector2f WallAvoidance::getSteeringForce(entt::entity otherEntity, AiComponent& aiComponent,
                                             PositionComponent& positionComponent,
                                             SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f force{};
    sf::Vector2f closestIntersectionPoint{};

    const auto& position = positionComponent.mPosition;
    const auto& whiskers = createWhiskers(positionComponent, steeringBehaviourComponent);

    for (auto whiskerItr = 0; whiskerItr < whiskers.size(); ++whiskerItr)
    {

        sf::Vector2f intersectionPoint{};
        std::pair<int, int> points{-1, -1};
        for (auto wallIter = 0; wallIter < mCollisions.size(); ++wallIter)
        {
            int wallID = -1;
            auto& wall = mCollisions[wallIter];
            sf::Vector2f first = getPoint(wall, 0);
            sf::Vector2f second = getPoint(wall, 1);
            sf::Vector2f third = getPoint(wall, 2);
            sf::Vector2f forth = getPoint(wall, 3);

            if (LineCollision(position, whiskers[whiskerItr], second, first, &intersectionPoint))
            {
                if (compareIntersectionPoints(position, intersectionPoint, closestIntersectionPoint,
                                              wallID, wallIter))
                {
                    points = {1, 0};
                }
            }
            if (LineCollision(position, whiskers[whiskerItr], first, forth, &intersectionPoint))
            {

                if (compareIntersectionPoints(position, intersectionPoint, closestIntersectionPoint,
                                              wallID, wallIter))
                {
                    points = {0, 3};
                }
            }
            if (LineCollision(position, whiskers[whiskerItr], third, second, &intersectionPoint))
            {
                if (compareIntersectionPoints(position, intersectionPoint, closestIntersectionPoint,
                                              wallID, wallIter))
                {
                    points = {2, 1};
                }
            }
            if (LineCollision(position, whiskers[whiskerItr], forth, third, &intersectionPoint))
            {
                if (compareIntersectionPoints(position, intersectionPoint, closestIntersectionPoint,
                                              wallID, wallIter))
                {
                    points = {3, 2};
                }
            }
            if (wallID >= 0)
            {

                sf::Vector2f vThroughWall = whiskers[whiskerItr] - closestIntersectionPoint;
                auto beg = getPoint(mCollisions[wallID], points.first);
                auto end = getPoint(mCollisions[wallID], points.second);
                auto collidingSideOfWall = end - beg;
                auto normalToWall = perpendicular(normalizeVector(collidingSideOfWall));

                auto vectorThroughWallLength = calculateVectorLength(vThroughWall);
                force = normalToWall * vectorThroughWallLength;
                steeringBehaviourComponent.normal = {closestIntersectionPoint + force,
                                                     closestIntersectionPoint};

                if (isFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::WANDER))
                {
                    adjustWanderPoint(aiComponent, positionComponent, steeringBehaviourComponent,
                                      force);
                }
            }
        }
    }
    return force;
}