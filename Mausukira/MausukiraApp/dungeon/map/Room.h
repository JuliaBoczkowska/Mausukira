#ifndef ROOM_H
#define ROOM_H

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <vector>

class Room
{
public:
    enum class RoomGridType
    {
        NONE = 0,
        ROOM = 1,
        ENEMY = 2
    };
    using RoomGrid = std::vector<std::vector<int>>;

    Room() = default;
    explicit Room(sf::Vector2i location, sf::Vector2i size, std::vector<std::vector<int>> grid,
                  sf::Vector2f center);

    void draw(sf::RenderWindow& window);
    static void setCenter(sf::Vector2f center);
    bool collide(Room& otherRom);

public:
    static sf::Vector2f centerOfAllPoints;
    sf::Vector2i mLocation;
    sf::Vector2i mSize;
    RoomGrid mGrid;
    sf::Vector2f mCenter{0, 0};

private:
    sf::IntRect bounding;
    sf::CircleShape shape;
};

#endif// ROOM_H
