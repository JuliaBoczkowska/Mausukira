#ifndef COORDINATE_H
#define COORDINATE_H

#include "SFML/System/Vector2.hpp"
#include <functional>

namespace as::helper
{
    struct Coordinate
    {
        Coordinate(sf::Vector2i coord)
            : x(coord.x)
            , y(coord.y)
        {

        }

        bool operator==(const Coordinate& other) const
        {
            return (x == other.x) && (y == other.y);
        }

        bool operator<(const Coordinate& other) const
        {
            return (this->x < other.x) || ((this->x == other.x) && (this->y < other.y));
        }

        int x;
        int y;
    };
}

namespace std
{
    template<>
    struct hash<as::helper::Coordinate>
    {
        std::size_t operator()(const as::helper::Coordinate& coord) const
        {
            return ((hash<int>()(coord.x) ^ (hash<int>()(coord.x) << 1)) >> 1);
        }
    };
}

#endif //COORDINATE_H
