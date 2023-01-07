#include "EnemyStateSystem.h"
#include "AttackStateSystem.h"
#include "EnemyState.h"
#include "IdleStateSystem.h"
#include "dungeon/map/MapContext.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/EnemyComponent.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/SteeringBehaviourComponent.h"
#include "ecs/components/VelocityComponent.h"
#include "ecs/entities/Player.h"
#include "utils/Math.h"

EnemyStateSystem::EnemyStateSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mSteeringBehaviour(mapContext)
{
    mEnemyBehaviourMap.insert({MobState::Attacking, std::make_unique<AttackStateSystem>(
                                                        (*this), mSteeringBehaviour, mRegistry)});
    mEnemyBehaviourMap.insert({MobState::Idle, std::make_unique<IdleStateSystem>(
                                                   (*this), mSteeringBehaviour, mRegistry)});

    PositionComponent* playerPositionComponent;
    mRegistry.view<PlayerComponent, PositionComponent>().each(
        [&](PlayerComponent& playerComponent, PositionComponent& positionComponent)
        {
            playerPositionComponent = &positionComponent;
        });

    mRegistry.view<AiComponent, EnemyComponent, PositionComponent, SteeringBehaviourComponent>()
        .each(
            [&](AiComponent& aiComponent, EnemyComponent& enemyComponent,
                PositionComponent& positionComponent, SteeringBehaviourComponent& steering)
            {
                sf::Vector2f newHeading = normalizeVector(playerPositionComponent->mPosition -
                                                          positionComponent.mPosition);
                steering.mDirectionVector = newHeading;
                steering.mSideVectorToDirection = perpendicular(newHeading);
                aiComponent.mPlayerPositionComponent = playerPositionComponent;
            });
}

#include <cmath>

void EnemyStateSystem::update(const sf::Time& dt)
{
    sf::Vector2f force;
    if (std::isnan(force.x) || std::isnan(force.y))
    {
        std::cout << "THATS BED" << std::endl;
    }

    auto view =
        mRegistry
            .view<EntityState, VelocityComponent, SteeringBehaviourComponent, PositionComponent>();
    for (auto entity: view)
    {

        auto [entityState, velocity, steering, position] = view.get(entity);
        switch (entityState.state)
        {
            case MobState::Idle:
                force = mEnemyBehaviourMap[MobState::Idle].get()->update(dt, entity);
                break;
            case MobState::Attacking:
                force = mEnemyBehaviourMap[MobState::Attacking].get()->update(dt, entity);
                break;
            case MobState::Died: break;
        }
        // if no steering force is produced decelerate the player by applying a
        // braking force
        if (force == sf::Vector2f{0, 0})
        {
            float BrakingRate = 0.8;

            velocity.mVelocity *= BrakingRate;
        }

        // calculate the acceleration
        sf::Vector2f accel = force / steering.mMass;
        velocity.mVelocity += accel;
        velocity.mVelocity = truncate(velocity.mVelocity, steering.maxSpeed);

        position.mPosition += velocity.mVelocity;
        steering.mDirectionVector = normalizeVector(velocity.mVelocity);
        steering.mSideVectorToDirection = perpendicular(steering.mDirectionVector);
    }
}