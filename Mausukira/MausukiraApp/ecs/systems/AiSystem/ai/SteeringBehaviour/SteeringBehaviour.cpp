#include "SteeringBehaviour.h"
#include "Arrive.h"
#include "Flee.h"
#include "Rest.h"
#include "Separation.h"
#include "WallAvoidance.h"
#include "Wander.h"
#include "dungeon/map/MapContext.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "utils/Math.h"

SteeringBehaviour::SteeringBehaviour(MapContext& tileMap, entt::registry& registry)
    : mTileMap(tileMap)
    , mRegistry(registry)
{
    for (auto tile: mTileMap.noTraversableTiles)
    {
        collisions.push_back(&tile->mRectangle);
    }

    mSteeringBehaviours.emplace(EnemyBehaviour::SEPARATION,
                                std::make_unique<Separation>(mRegistry));
    mSteeringBehaviours.emplace(EnemyBehaviour::WANDER, std::make_unique<Wander>(mRegistry));
    mSteeringBehaviours.emplace(EnemyBehaviour::WALL_AVOIDANCE,
                                std::make_unique<WallAvoidance>(mRegistry, collisions));
    mSteeringBehaviours.emplace(EnemyBehaviour::ARRIVE, std::make_unique<Arrive>(mRegistry));
    mSteeringBehaviours.emplace(EnemyBehaviour::SEPARATION,
                                std::make_unique<Separation>(mRegistry));
    mSteeringBehaviours.emplace(EnemyBehaviour::REST, std::make_unique<Rest>(mRegistry));
    mSteeringBehaviours.emplace(EnemyBehaviour::FLEE, std::make_unique<Flee>(mRegistry));

    mRegistry.view<SteeringBehaviourComponent>().each(
        [&](SteeringBehaviourComponent& steeringBehaviourComponent)
        {
            setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::WANDER);
            setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::WALL_AVOIDANCE);
            setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::SEPARATION);
        });
}

sf::Vector2f SteeringBehaviour::getSteeringForce(
    entt::entity entity, AiComponent& aiComponent, PositionComponent& positionComponent,
    SteeringBehaviourComponent& steeringBehaviourComponent)
{
    sf::Vector2f forceTotal{};
    sf::Vector2f force{};
    auto steeringBehaviourFlag = steeringBehaviourComponent.mBehaviourFlag;

    if (isFlagOn(steeringBehaviourFlag, EnemyBehaviour::WALL_AVOIDANCE))
    {
        auto steeringForce = mSteeringBehaviours.find(EnemyBehaviour::WALL_AVOIDANCE)
                                 ->second->getSteeringForce(entity, aiComponent, positionComponent,
                                                            steeringBehaviourComponent);
        force = steeringForce * mWallAvoidanceWeight;
        if (!sumUpForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
        {
            return forceTotal;
        }
    }

    if (isFlagOn(steeringBehaviourFlag, EnemyBehaviour::REST))
    {
        auto steeringForce = mSteeringBehaviours.find(EnemyBehaviour::REST)
                                 ->second->getSteeringForce(entity, aiComponent, positionComponent,
                                                            steeringBehaviourComponent);
        force = steeringForce * mRestWeight;
        if (!sumUpForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
        {
            return forceTotal;
        }
    }

    if (isFlagOn(steeringBehaviourFlag, EnemyBehaviour::SEPARATION))
    {
        auto steeringForce = mSteeringBehaviours.find(EnemyBehaviour::SEPARATION)
                                 ->second->getSteeringForce(entity, aiComponent, positionComponent,
                                                            steeringBehaviourComponent);
        force = steeringForce * mSeparationWeight;
        if (!sumUpForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
        {
            return forceTotal;
        }
    }

    if (isFlagOn(steeringBehaviourFlag, EnemyBehaviour::WANDER))
    {
        auto steeringForce = mSteeringBehaviours.find(EnemyBehaviour::WANDER)
                                 ->second->getSteeringForce(entity, aiComponent, positionComponent,
                                                            steeringBehaviourComponent);
        force = steeringForce * mWanderWeight;
        if (steeringBehaviourComponent.clock.getElapsedTime().asSeconds() >
            steeringBehaviourComponent.mActiveWanderTime * 10)
        {
            clearFlag(steeringBehaviourComponent.mBehaviourFlag);
            setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::REST);
            setFlagOn(steeringBehaviourComponent.mBehaviourFlag, EnemyBehaviour::SEPARATION);
            steeringBehaviourComponent.clock.restart();
        }
        if (!sumUpForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
        {
            return forceTotal;
        }
    }

    if (isFlagOn(steeringBehaviourFlag, EnemyBehaviour::ARRIVE))
    {
        auto steeringForce = mSteeringBehaviours.find(EnemyBehaviour::ARRIVE)
                                 ->second->getSteeringForce(entity, aiComponent, positionComponent,
                                                            steeringBehaviourComponent);
        force = steeringForce * mSeekWeight;
        if (!sumUpForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
        {
            return forceTotal;
        }
    }

    if (isFlagOn(steeringBehaviourFlag, EnemyBehaviour::FLEE))
    {
        auto steeringForce = mSteeringBehaviours.find(EnemyBehaviour::FLEE)
                                 ->second->getSteeringForce(entity, aiComponent, positionComponent,
                                                            steeringBehaviourComponent);
        force = steeringForce * mFleeWeight;
        if (!sumUpForces(forceTotal, force, steeringBehaviourComponent.mMaxForce))
        {
            return forceTotal;
        }
    }

    return forceTotal;
}

bool SteeringBehaviour::sumUpForces(sf::Vector2f& totalForce, sf::Vector2f forceToAdd,
                                    float maxForce)
{
    if (forceToAdd == sf::Vector2f{0, 0})
    {
        return true;
    }
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