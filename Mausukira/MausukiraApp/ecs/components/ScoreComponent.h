#ifndef SCORECOMPONENT_H
#define SCORECOMPONENT_H

#include "SFML/Graphics/Text.hpp"
#include "dungeon/map/Constants.h"

struct ScoreComponent
{
    ScoreComponent(int score)
    {
        this->score = score;
        font.loadFromFile("resources/arial.ttf");

        counter.setFont(font);
        counter.setCharacterSize(36);
        counter.setFillColor(sf::Color::White);
        counter.setOutlineThickness(0.4f);

        mLevelNumber.setFont(font);
        mLevelNumber.setCharacterSize(36);
        mLevelNumber.setFillColor(sf::Color::White);
        mLevelNumber.setOutlineThickness(0.4f);

        auto textRect = counter.getLocalBounds();
        counter.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
        counter.setPosition(20, 7);

        textRect = counter.getLocalBounds();
        mLevelNumber.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top + textRect.height / 2.0f);
        mLevelNumber.setPosition(400, 7);

        rectangle.setSize(sf::Vector2f(MAP_SIZE_X_WORLD_COORD, MAP_SIZE_Y_WORLD_COORD * 0.07f));
        rectangle.setFillColor(sf::Color(255, 255, 255, 70));
    }

    int score{0};
    sf::Text counter;
    sf::Text mLevelNumber;
    sf::Font font;
    sf::RectangleShape rectangle;
};


#endif// SCORECOMPONENT_H
