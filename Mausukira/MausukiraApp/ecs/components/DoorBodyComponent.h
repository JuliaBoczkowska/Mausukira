#ifndef DOORBODYCOMPONENT_H
#define DOORBODYCOMPONENT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "dungeon/map/Constants.h"

struct DoorBodyComponent
{
    explicit DoorBodyComponent(sf::Vector2f position)
    {
        doorShape.setFillColor(sf::Color::Magenta);
        doorShape.setSize({ TILE_SIZE, TILE_SIZE });
        doorShape.setPosition(position);
    }

    sf::RectangleShape doorShape;
    bool changeLevel{ false };
};

#endif //DOORBODYCOMPONENT_H
