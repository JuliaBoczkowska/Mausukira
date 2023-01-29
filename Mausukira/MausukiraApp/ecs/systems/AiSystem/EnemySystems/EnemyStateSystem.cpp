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
#include "utils/Math.h"

EnemyStateSystem::EnemyStateSystem(entt::registry& registry, MapContext& mapContext,
                                   std::vector<std::unique_ptr<Enemy>>& enemyEntity)
    : System(registry)
    , mSteeringBehaviour(mapContext, registry)
    , mEnemyEntity(enemyEntity)
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

    mRegistry
        .view<AiComponent, EnemyComponent, PositionComponent, SteeringBehaviourComponent,
              VelocityComponent>()
        .each(
            [&](AiComponent& aiComponent, EnemyComponent& enemyComponent,
                PositionComponent& positionComponent, SteeringBehaviourComponent& steering,
                VelocityComponent& velocityComponent)
            {
                sf::Vector2f newHeading = normalizeVector(playerPositionComponent->mPosition -
                                                          positionComponent.mPosition);
                steering.mDirectionVector = newHeading;
                steering.mSideVectorToDirection = perpendicular(newHeading);
                aiComponent.mPlayerPositionComponent = playerPositionComponent;
                aiComponent.mVelocity = &velocityComponent;
            });
}

void EnemyStateSystem::indicateWhichEnemiesAreClose(entt::entity selectedEntity)
{
    auto positionSelectedEntity = mRegistry.get<PositionComponent>(selectedEntity);

    mRegistry
        .view<AiComponent, EnemyComponent, PositionComponent, SteeringBehaviourComponent,
              VelocityComponent>()
        .each(
            [&](auto entity, AiComponent& aiComponent, EnemyComponent& enemyComponent,
                PositionComponent& positionComponent, SteeringBehaviourComponent& steering,
                VelocityComponent& velocityComponent)
            {
                steering.isInCloseDistanceWithOtherEnemy = false;

                sf::Vector2f vecEnemyToEnemy =
                    positionComponent.mPosition - positionSelectedEntity.mPosition;
                double range = 30;

                auto lengthSquared = (vecEnemyToEnemy.x * vecEnemyToEnemy.x) +
                                     (vecEnemyToEnemy.y * vecEnemyToEnemy.y);
                if ((entity != selectedEntity) && (lengthSquared < range * range))
                {
                    steering.isInCloseDistanceWithOtherEnemy = true;
                }
            });
}

void EnemyStateSystem::update(const sf::Time& dt)
{
    sf::Vector2f force;
    auto view = mRegistry.view<EntityState, VelocityComponent, SteeringBehaviourComponent,
                               PositionComponent, AiComponent>();
    for (auto entity: view)
    {
        /** Crucial for separation behaviour */
        indicateWhichEnemiesAreClose(entity);
        auto [entityState, velocity, steering, position, aiComponent] = view.get(entity);
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
        /** When no force is applied slow down enemy */
        whenNoForceSlowDownEnemy(force, velocity.mVelocity, steering.deceleration);
        calculateNewVelocity(force, velocity.mVelocity, steering, aiComponent);

        position.mPosition += velocity.mVelocity;
        steering.mDirectionVector = normalizeVector(velocity.mVelocity);
        steering.mSideVectorToDirection = perpendicular(steering.mDirectionVector);
    }
}
void EnemyStateSystem::calculateNewVelocity(const sf::Vector2f& force, sf::Vector2f& velocity,
                                            SteeringBehaviourComponent& steering,
                                            AiComponent& aiComponent) const
{
    sf::Vector2f acceleration = force / steering.mMass;
    velocity += acceleration;
    velocity = truncate(velocity, steering.maxSpeed);
    aiComponent.mVelocity->mVelocity = velocity;
}

void EnemyStateSystem::whenNoForceSlowDownEnemy(const sf::Vector2f& force, sf::Vector2f& velocity,
                                                const float& deceleration) const
{
    if (force == sf::Vector2f{0, 0})
    {
        velocity *= deceleration;
    }
}
