#include "SteeringBehaviour.h"
#include "dungeon/map/MapContext.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "utils/Math.h"
#include "utils/RandomNumberGenerator.h"


sf::Vector2f SteeringBehaviour::seek(const AiComponent& aiComponent,
                                     const PositionComponent& positionComponent,
                                     SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f velocity;
    /** Obtain the direction to the player. */
    velocity = aiComponent.mPlayerPositionComponent->mPosition - positionComponent.mPosition;

    /** Obtain velocity at max speed in the player's direction. */
    velocity = normalizeVector(velocity);
    velocity = velocity * steeringBehaviourComponent.maxSpeed;

    return velocity;
}

sf::Vector2f SteeringBehaviour::arrive(const AiComponent& aiComponent,
                                       const PositionComponent& positionComponent,
                                       SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f velocity{0, 0};
    /** Obtain the direction to the player. */
    velocity = aiComponent.mPlayerPositionComponent->mPosition - positionComponent.mPosition;

    if (calculateVectorLength(velocity) > mArriveRadius)
    {
        /** Result is defined as timeToTarget in seconds */
        velocity = velocity / mArriveTimeToTarget;

        /** If the obtained velocity is bigger than maxSpeed  */
        if (calculateVectorLength(velocity) > steeringBehaviourComponent.maxSpeed)
        {
            /** Obtain velocity at max speed in the player's direction. */
            velocity = normalizeVector(velocity);
            velocity = velocity * steeringBehaviourComponent.maxSpeed;
        }
        return velocity;
    }
    else
    {
        /** Obtain velocity at max speed in the player's direction. */
        velocity = normalizeVector(velocity);
        velocity = velocity * steeringBehaviourComponent.maxSpeed;
    }

    return velocity;
}


sf::Vector2f SteeringBehaviour::wander(AiComponent& aiComponent,
                                       PositionComponent& positionComponent,
                                       SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f force;
    /** Add some little random step to wander position */
    auto rnd1 = generateFloatNumberInRange(-1, 1);
    auto rnd2 = generateFloatNumberInRange(-1, 1);
    sf::Vector2f temp(rnd1, rnd2);
    aiComponent.mWanderPoint += temp * mMaxAmountOfRandomDisplacement;

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
    force = pointWorldSpace - positionComponent.mPosition;
    force = normalizeVector(force);
    return force;
}

sf::Vector2f SteeringBehaviour::separate(const std::list<ColliderComponent*>& agents)
{
    return sf::Vector2f();
}

float PerpDot(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return (a.y * b.x) - (a.x * b.y);
}

bool LineCollision(const sf::Vector2f& A1, const sf::Vector2f& A2, const sf::Vector2f& B1,
                   const sf::Vector2f& B2, sf::Vector2f* out)
{
    sf::Vector2f a(A2 - A1);
    sf::Vector2f b(B2 - B1);
    sf::Vector2f c(B2 - A2);

    float f = PerpDot(a, b);

    // lines are parallel
    if (!f)
    {
        return false;
    }

    float aa = PerpDot(a, c);
    float bb = PerpDot(b, c);


    if (f < 0)
    {
        if (aa > 0)
        {
            return false;
        }
        if (bb > 0)
        {
            return false;
        }
        if (aa < f)
        {
            return false;
        }
        if (bb < f)
        {
            return false;
        }
    }
    else
    {
        if (aa < 0)
        {
            return false;
        }
        if (bb < 0)
        {
            return false;
        }
        if (aa > f)
        {
            return false;
        }
        if (bb > f)
        {
            return false;
        }
    }

    if (out)
    {
        *out = b * (1.0f - (aa / f)) + B1;
    }// assigns the point of intersection

    return true;
}

sf::Vector2f SteeringBehaviour::avoidWalls(AiComponent& aiComponent,
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
        for (auto wallIter = 0; wallIter < collisions.size(); ++wallIter)
        {
            int wallID = -1;
            auto& wall = collisions[wallIter];
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
                auto beg = getPoint(collisions[wallID], points.first);
                auto end = getPoint(collisions[wallID], points.second);
                auto collidingSideOfWall = end - beg;
                auto normalToWall = perpendicular(normalizeVector(collidingSideOfWall));

                auto vectorThroughWallLength = calculateVectorLength(vThroughWall);
                force = normalToWall * vectorThroughWallLength;
                steeringBehaviourComponent.normal = {closestIntersectionPoint + force,
                                                     closestIntersectionPoint};

                aiComponent.mWanderPoint += force * mMaxAmountOfRandomDisplacement;

                /** Make a unit vector */
                aiComponent.mWanderPoint = normalizeVector(aiComponent.mWanderPoint);

                /** Make the length of the vector the same as radius */
                aiComponent.mWanderPoint *= mWanderRadius;
            }
        }
    }
    return force;
}

bool SteeringBehaviour::compareIntersectionPoints(const sf::Vector2f& position,
                                                  const sf::Vector2f& intersectionPoint,
                                                  sf::Vector2f& closestIntersectionPoint,
                                                  int& wallID, int& wallIter) const
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


sf::Vector2f SteeringBehaviour::getPoint(sf::RectangleShape* const& collider, int i) const
{
    sf::Transform matrix = collider->getTransform();
    return matrix.transformPoint(collider->getPoint(i));
}

std::array<sf::Vector2f, 3> SteeringBehaviour::createWhiskers(
    const PositionComponent& positionComponent,
    SteeringBehaviourComponent& steeringBehaviourComponent) const
{
    std::array<sf::Vector2f, 3> whiskers;
    auto position = positionComponent.mPosition;
    auto heading = steeringBehaviourComponent.mDirectionVector;

    sf::Vector2f centralRay = position + mWhiskerLength * heading;


    auto rotatedHeading = rotateBy(15, heading);
    sf::Vector2f leftWhisker = position + mWhiskerLength / 2 * rotatedHeading;

    rotatedHeading = rotateBy(-15, heading);
    sf::Vector2f rightWhisker = position + mWhiskerLength / 2 * rotatedHeading;

    whiskers.at(0) = leftWhisker;
    whiskers.at(1) = centralRay;
    whiskers.at(2) = rightWhisker;

    /** In order to be drawn they need to be stored in each enemy */
    steeringBehaviourComponent.whiskers = whiskers;
    return whiskers;
}

sf::Vector2f SteeringBehaviour::getSteeringForce(
    AiComponent& aiComponent, PositionComponent& positionComponent,
    SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f forceTotal{};
    sf::Vector2f forceToAdd{};
    sf::Vector2f force{};
    switch (aiComponent.state)
    {
        case EnemyGoal::ARRIVE:
            return arrive(aiComponent, positionComponent, steeringBehaviourComponent);

        case EnemyGoal::SEEK:
            force = avoidWalls(aiComponent, positionComponent, steeringBehaviourComponent) *
                    mWallAvoidanceWeight;
            if (!accumulateForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
            {
                return forceTotal;
            }
            force =
                seek(aiComponent, positionComponent, steeringBehaviourComponent) * mSeekWeight;
            if (!accumulateForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
            {
                return forceTotal;
            }
            return forceTotal;


        case EnemyGoal::WANDER:
            force = avoidWalls(aiComponent, positionComponent, steeringBehaviourComponent) *
                    mWallAvoidanceWeight;
            if (!accumulateForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
            {
                return forceTotal;
            }
            force =
                wander(aiComponent, positionComponent, steeringBehaviourComponent) * mWanderWeight;
            if (!accumulateForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
            {
                return forceTotal;
            }
            return forceTotal;
    }
}

bool SteeringBehaviour::accumulateForces(sf::Vector2f& totalForce, sf::Vector2f forceToAdd,
                                         float maxForce)
{
    auto totalForceLength = calculateVectorLength(totalForce);
    auto remainingForceLength = maxForce - totalForceLength;
    auto forceToAddLength = calculateVectorLength(forceToAdd);

    if (remainingForceLength < 0.f)
    {
        return false;
    }

    if (forceToAddLength < remainingForceLength)
    {
        totalForce += forceToAdd;
    }
    else
    {
        forceToAddLength = remainingForceLength;
        totalForce += normalizeVector(forceToAdd) * forceToAddLength;
    }
    return true;
}

SteeringBehaviour::SteeringBehaviour(MapContext& tileMap)
    : mTileMap(tileMap)
{
    for (auto tile: mTileMap.noTraversableTiles)
    {
        tile->mSprite.setColor(sf::Color::Magenta);
        collisions.push_back(&tile->mRectangle);
    }
}
