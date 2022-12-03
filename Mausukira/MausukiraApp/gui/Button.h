#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include <functional>

class Button : public virtual Component
{
public:
    explicit Button();
    ~Button() = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setCallback(std::function<void()> action);
    void setText(const std::string& buttonText);

    std::function<void()> callback;


private:
    sf::Text text;
    sf::RectangleShape rectangle;
};

#endif// BUTTON_H
