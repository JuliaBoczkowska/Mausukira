#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "ColliderComponent.h"
#include "SFML/System/Vector2.hpp"
#include "scene/CollisionBox.h"

struct TransformComponent
{
    TransformComponent(ColliderComponent& colliderComponent, sf::Vector2f position);
    TransformComponent(const TransformComponent&);
    TransformComponent(TransformComponent&& c) noexcept;
    TransformComponent& operator=(TransformComponent&& other);

    const sf::Vector2f& operator()();
    const sf::Vector2f& operator()() const;
    void setPosition(sf::Vector2f position);
    sf::Vector2f position();
    void moveBy(const sf::Vector2f& mov);

    sf::Vector2f mPosition{0.f, 0.f};
    sf::Vector2f mPositionOld;
    float mScale{2.f};
    ColliderComponent& mColliderComponent;
};

#endif// TRANSFORMCOMPONENT_H
