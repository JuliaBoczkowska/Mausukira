#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "SFML/System/Vector2.hpp"

struct TransformComponent
{
    sf::Vector2f mPosition{ 0.f, 0.f };

    TransformComponent() = default;

    TransformComponent(const TransformComponent&) = default;

    TransformComponent(const sf::Vector2f& position)
        : mPosition(position)
    {
    }

    const sf::Vector2f& operator()()
    {
        return mPosition;
    }

    const sf::Vector2f& operator()() const
    {
        return mPosition;
    }

    void SetPosition(sf::Vector2f position)
    {
        mPosition = position;
    }
};

#endif//TRANSFORMCOMPONENT_H
