#include "LevelChangeSystem.h"
#include "ecs/components/EntityComponent.h"
#include "ecs/entities/Entity.h"
#include "ecs/components/PositionComponent.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/DoorBodyComponent.h"
#include "states_stack/states/State.h"
#include "states_stack/LevelInfo.h"


LevelChangeSystem::LevelChangeSystem(entt::registry& registry, LevelInfo& levelInfo)
    : System(registry)
    , mLevelInfo(levelInfo)
{

}

void LevelChangeSystem::update(const sf::Time& dt)
{
    whenEnemyIsDeadCreateDoor();
    auto view = mRegistry.view<DoorBodyComponent>();
    for (auto& entity: view)
    {
        auto [doorBodyComponent] = view.get(entity);

        if (doorBodyComponent.changeLevel)
        {
            mLevelInfo.changeNextLevel = true;
        }
    }
}

void LevelChangeSystem::whenEnemyIsDeadCreateDoor()
{
    auto view = mRegistry.view<EntityState, EntityStatistic, PositionComponent>();
    for (auto& entity: view)
    {
        auto [entityState, entityStatistic, positionComponent] = view.get(entity);

        if (entityState.state == MobState::Died)
        {
            if (entityStatistic.isTransitionToNextLevel)
            {
                Entity doorToNextLevel = { mRegistry.create(), &mRegistry };
                doorToNextLevel.addComponent<PositionComponent>(positionComponent.mPosition);
                doorToNextLevel.assignComponent<DoorBodyComponent>(positionComponent.mPosition);
            }
        }
    }
}
