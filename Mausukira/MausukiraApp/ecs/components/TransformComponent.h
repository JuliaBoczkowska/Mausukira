//#ifndef TRANSFORMCOMPONENT_H
//#define TRANSFORMCOMPONENT_H
//
//#include "SFML/System/Vector2.hpp"
//
//struct TransformComponent
//{
//    TransformComponent(ColliderComponent& colliderComponent, SpriteComponent& spriteComponent,
//        HealthComponent& healthComponent, sf::Vector2f position);
//
//    TransformComponent(const TransformComponent&);
//
//    TransformComponent(TransformComponent&& c) noexcept;
//
//    TransformComponent& operator=(TransformComponent&& other);
//
//    const sf::Vector2f& operator()();
//
//    const sf::Vector2f& operator()() const;
//
//    void setPosition(sf::Vector2f position);
//
//    void moveBy(const sf::Vector2f& mov);
//
//
//    sf::Vector2f mVelocity{ 0.f, 0.f };
//};
//
//#endif// TRANSFORMCOMPONENT_H
