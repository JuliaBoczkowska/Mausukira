#ifndef SPATIALHASH_H
#define SPATIALHASH_H

#include <unordered_map>
#include <unordered_set>
#include <set>
#include "ecs/components/ColliderComponent.h"

class SpatialHash
{

public:
    SpatialHash() = default;

    void clearSpatialGridMap();

    void update(ColliderComponent& collider);

    void addCollider(ColliderComponent& collider, int key);

    std::set<ColliderComponent*> getCollidersInTheSameCell(ColliderComponent& collider);

private:
    int getArrayCoordinates(const ColliderComponent& collider, int i) const;

private:
    std::unordered_map<int, std::unordered_set<ColliderComponent*>> mSpatialHashGrid{};
};


#endif //SPATIALHASH_H
