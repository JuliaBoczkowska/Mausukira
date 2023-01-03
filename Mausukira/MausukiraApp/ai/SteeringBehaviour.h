#ifndef STEERINGBEHAVIOUR_H
#define STEERINGBEHAVIOUR_H


#include "SFML/System/Vector2.hpp"

class SteeringBehaviour
{
    SteeringBehaviour();

    sf::Vector2f seek(sf::Vector2f& v);

    sf::Vector2f flee(sf::Vector2f& v);

    sf::Vector2f arrive(sf::Vector2f& v);
};


#endif //STEERINGBEHAVIOUR_H
