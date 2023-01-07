#ifndef ENEMYSTATESYSTEM_H
#define ENEMYSTATESYSTEM_H
#include "EnemyState.h"
#include "ai/SteeringBehaviour.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/systems/System.h"
#include "unordered_map"

class MapContext;
class EnemyStateSystem : public System
{
public:
    using EnemyBehaviourMap = std::unordered_map<MobState, std::unique_ptr<EnemyState>>;

    EnemyStateSystem(entt::registry& registry, MapContext& mapContext);

    void update(const sf::Time& dt) override;

private:
    EnemyBehaviourMap mEnemyBehaviourMap;
    SteeringBehaviour mSteeringBehaviour;
};


#endif// ENEMYSTATESYSTEM_H
