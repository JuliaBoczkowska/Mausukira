#include "Button.h"
#include "SFML/Graphics/RenderTarget.hpp"

void Button::setCallback(std::function<void()> action)
{
    callback = action;
}

void Button::setText(const std::string& buttonText)
{
    text.setString(buttonText);
}

Button::Button()
{
    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(10, 20);
    text.setPosition(rectangle.getPosition());
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rectangle, states);
}
