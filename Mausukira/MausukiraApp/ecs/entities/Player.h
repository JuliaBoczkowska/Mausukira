#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Scene;

class Player
{
public:
    Player(Scene* scene);

private:
    void setupColliderRelationship(Entity& player, Entity& colliderFoot, Entity& colliderBody) const;

    void setupColliders(const sf::Sprite& sprite, Scene*& scene, Entity& colliderFoot, Entity& colliderBody) const;

    sf::Sprite& setupPlayer(Scene* scene, sf::Sprite& sprite, Entity& player) const;

    void setupWeapon(Scene* scene, Entity& player) const;
};

#endif// PLAYER_H
