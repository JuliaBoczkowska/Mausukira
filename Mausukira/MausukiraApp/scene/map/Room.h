#ifndef ROOM_H
#define ROOM_H

#include "SFML/Graphics/Rect.hpp"
#include <vector>

class Room
{
    using RoomGrid = std::vector<std::vector<int>>;

public:
    explicit Room(sf::Vector2i location, sf::Vector2i size, RoomGrid grid, sf::Vector2f center);

    Room() = default;

    static sf::Vector2f centerOfAllPoints;

    static void setCenter(sf::Vector2f center)
    {
        centerOfAllPoints = center;
    }

    bool collide(Room& otherRom)
    {
        return otherRom.bounding.intersects(this->bounding);
    }

public:
    sf::Vector2i mLocation;
    sf::Vector2i mSize;
    RoomGrid mGrid;
    sf::Vector2f mCenter{0, 0};

private:
    sf::IntRect bounding;
};

#endif// ROOM_H
