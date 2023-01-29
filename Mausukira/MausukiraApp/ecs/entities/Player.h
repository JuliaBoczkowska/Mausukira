#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "states_stack/LevelInfo.h"

class Scene;
class SharedContext;

class Player
{
public:
    Player(Scene* scene, SharedContext& mSharedContext, LevelInfo& levelInfo);

private:
    void setupColliderRelationship(Entity& player, Entity& colliderFoot,
                                   Entity& colliderBody) const;

    void setupColliders(const sf::Sprite& sprite, Scene*& scene, Entity& colliderFoot,
                        Entity& colliderBody) const;

    sf::Sprite& setupPlayer(Scene* scene, sf::Sprite& sprite, Entity& player,
                            LevelInfo& levelInfo) const;

    void setupWeapon(Scene* scene, Entity& player) const;
};

#endif// PLAYER_H
