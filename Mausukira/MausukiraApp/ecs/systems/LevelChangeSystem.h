#ifndef LEVELCHANGESYSTEM_H
#define LEVELCHANGESYSTEM_H

#include "System.h"

class LevelInfo;

class LevelChangeSystem : public System
{
public:
    explicit LevelChangeSystem(entt::registry& registry, LevelInfo& levelInfo);

    void update(const sf::Time& dt) override;

    void whenEnemyIsDeadCreateDoor();

private:
    LevelInfo& mLevelInfo;
};


#endif //LEVELCHANGESYSTEM_H
