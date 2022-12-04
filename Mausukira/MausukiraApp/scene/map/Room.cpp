#include "Room.h"

Room::Room(sf::Vector2i location, sf::Vector2i size, Room::RoomGrid grid, sf::Vector2f center)
    : mLocation(location)
    , mSize(size)
    , mGrid(grid)
    , mCenter(center)
{
    shape.setRadius(2);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(center);
    bounding = sf::IntRect(mLocation, mSize);
}

sf::Vector2f Room::centerOfAllPoints = {0, 0};

bool Room::collide(Room& otherRom)
{
    return otherRom.bounding.intersects(this->bounding);
}

void Room::setCenter(sf::Vector2f center)
{
    centerOfAllPoints = center;
}
void Room::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
