#ifndef HASHFN_H
#define HASHFN_H

#include "dungeon/map/Constants.h"
#include <set>

class HashFn
{
public:
    size_t operator()(const sf::Vector2i& v) const
    {
        // Hash function taken from http://howlingmoonsoftware.com/wordpress/collision-detection-and-spatial-indexes/
        return (static_cast<int>(v.x) * 1640531513 ^
                static_cast<int>(v.y) * 2654435789) % MAP_SIZE;
    }
};


#endif //HASHFN_H
