#ifndef SCORECOMPONENT_H
#define SCORECOMPONENT_H

#include "SFML/Graphics/Text.hpp"
#include "dungeon/map/Constants.h"

struct ScoreComponent
{
    ScoreComponent()
    {
        font.loadFromFile("resources/arial.ttf");

        counter.setFont(font);
        counter.setCharacterSize(40);
        counter.setFillColor(sf::Color::Black);
        counter.setOutlineColor(sf::Color::Black);
        counter.setOutlineThickness(0.4f);

        auto textRect = counter.getLocalBounds();
        counter.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        counter.setPosition(20, 7);

        rectangle.setSize(sf::Vector2f(MAP_SIZE_X_WORLD_COORD, MAP_SIZE_Y_WORLD_COORD * 0.07f));
        rectangle.setFillColor(sf::Color(255, 255, 255, 70));
    }

    int score{ 0 };
    sf::Text counter;
    sf::Font font;
    sf::RectangleShape rectangle;
};


#endif// SCORECOMPONENT_H
