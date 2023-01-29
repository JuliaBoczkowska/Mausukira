#ifndef ENEMYSTATESYSTEM_H
#define ENEMYSTATESYSTEM_H
#include "EnemyState.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/entities/enemy/Enemy.h"
#include "ecs/systems/AiSystem/ai/SteeringBehaviour/SteeringBehaviour.h"
#include "ecs/systems/System.h"
#include "unordered_map"

class MapContext;
class EnemyStateSystem : public System
{
public:
    using EnemyBehaviourMap = std::unordered_map<MobState, std::unique_ptr<EnemyState>>;

    EnemyStateSystem(entt::registry& registry, MapContext& mapContext,
                     std::vector<std::unique_ptr<Enemy>>& enemyEntity);

    void update(const sf::Time& dt) override;

private:
    void whenNoForceSlowDownEnemy(const sf::Vector2f& force, sf::Vector2f& velocity,
                                  const float& deceleration) const;
    void calculateNewVelocity(const sf::Vector2f& force, sf::Vector2f& velocity,
                              SteeringBehaviourComponent& steering, AiComponent& aiComponent) const;
    void indicateWhichEnemiesAreClose(entt::entity selectedEntity);

private:
    EnemyBehaviourMap mEnemyBehaviourMap;
    SteeringBehaviour mSteeringBehaviour;
    std::vector<std::unique_ptr<Enemy>>& mEnemyEntity;
};


#endif// ENEMYSTATESYSTEM_H
