#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "SFML/System/Vector2.hpp"

struct PositionComponent
{
    sf::Vector2f mPosition{ 0.f, 0.f };
    int mTileX;
    int mTileY;
};


#endif //POSITIONCOMPONENT_H
