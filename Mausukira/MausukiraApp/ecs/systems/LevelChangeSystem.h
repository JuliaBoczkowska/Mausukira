#ifndef LEVELCHANGESYSTEM_H
#define LEVELCHANGESYSTEM_H

#include "System.h"

class TextureManager;
class LevelInfo;

class LevelChangeSystem : public System
{
public:
    LevelChangeSystem(entt::registry& registry, LevelInfo& levelInfo,
                      TextureManager& textureManager);

    void update(const sf::Time& dt) override;

    void whenEnemyIsDeadCreateDoor();

private:
    LevelInfo& mLevelInfo;
    TextureManager& mTextureManager;
};


#endif// LEVELCHANGESYSTEM_H
