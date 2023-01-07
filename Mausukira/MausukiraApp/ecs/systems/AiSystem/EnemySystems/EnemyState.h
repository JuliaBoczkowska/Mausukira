#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "entt/entity/registry.hpp"
class SteeringBehaviour;
class EnemyStateSystem;

class EnemyState
{
public:
    explicit EnemyState(EnemyStateSystem& stateHandler, SteeringBehaviour& steeringBehaviour,
                        entt::registry& registry);

    virtual ~EnemyState() = default;

    virtual sf::Vector2f update(const sf::Time& dt, entt::entity entity) = 0;


protected:
    EnemyStateSystem& mSystemHandler;
    SteeringBehaviour& mSteeringBehaviour;
    entt::registry& mRegistry;
};

#endif// ENEMYSTATE_H
