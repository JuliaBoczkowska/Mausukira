#ifndef SPATIALHASH_H
#define SPATIALHASH_H

#include <unordered_map>
#include <unordered_set>
#include "ecs/components/ColliderComponent.h"
#include "HashFn.h"

class SpatialHash
{
public:
    SpatialHash();

    void addCollider(ColliderComponent& collider);

    void update(ColliderComponent& collider);

    void removeCollider(ColliderComponent& collider);

    std::set<ColliderComponent*> getCollidersInTheSameCell(ColliderComponent& collider);


private:
    std::unordered_map<sf::Vector2i, std::set<ColliderComponent*>, HashFn> mSpatialHashGrid{};

    sf::Vector2i getKey(const ColliderComponent& collider, int i) const;
};


#endif //SPATIALHASH_H
