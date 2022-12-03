#include "Room.h"

Room::Room(sf::Vector2i location, sf::Vector2i size, Room::RoomGrid grid, sf::Vector2f center)
    : mLocation(location)
    , mSize(size)
    , mGrid(grid)
    , mCenter(center)
{
    bounding = sf::IntRect(mLocation, mSize);
}

sf::Vector2f Room::centerOfAllPoints = {0, 0};