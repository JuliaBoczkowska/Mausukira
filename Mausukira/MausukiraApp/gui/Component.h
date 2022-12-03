#ifndef COMPONENT_H
#define COMPONENT_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Window/Event.hpp"

class Component : public sf::Drawable
{
public:
    explicit Component() = default;
    ~Component() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    bool isActive{false};
    bool isSelected{false};
};

#endif// COMPONENT_H
