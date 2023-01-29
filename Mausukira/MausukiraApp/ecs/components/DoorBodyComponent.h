#ifndef DOORBODYCOMPONENT_H
#define DOORBODYCOMPONENT_H

#include "dungeon/map/Constants.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct DoorBodyComponent
{
    DoorBodyComponent(sf::Vector2f position, const sf::Texture& texture)
    {
        doorShape.setFillColor(sf::Color::Magenta);
        doorShape.setSize({TILE_SIZE, TILE_SIZE});
        doorShape.setPosition(position);

        mDoorSprite.setTexture(texture);
        mDoorSprite.setScale({2, 2});
        mDoorSprite.setPosition(position);
    }

    sf::RectangleShape doorShape;
    sf::Sprite mDoorSprite;
    bool changeLevel{false};
};

#endif// DOORBODYCOMPONENT_H
