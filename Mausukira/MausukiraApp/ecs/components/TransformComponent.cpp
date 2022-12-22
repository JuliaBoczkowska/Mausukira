//#include "TransformComponent.h"
//#include "ColliderComponent.h"
//#include "HealthComponent.h"
//#include "SpriteComponent.h"
//
//
//const sf::Vector2f& TransformComponent::operator()()
//{
//    return mPosition;
//}
//
//const sf::Vector2f& TransformComponent::operator()() const
//{
//    return mPosition;
//}
//
//
//TransformComponent& TransformComponent::operator=(TransformComponent&& other)
//{
//    mColliderComponent = std::move(other.mColliderComponent);
//    mSpriteComponent = std::move(other.mSpriteComponent);
//    mPosition = std::move(other.mPosition);
//    return *this;
//}
//
//void TransformComponent::setPosition(sf::Vector2f position)
//{
//    mPosition = position;
//    mColliderComponent.setPosition(position);
//    mSpriteComponent.setPosition(position);
//}
//
//void TransformComponent::moveBy(const sf::Vector2f& mov)
//{
//    mPosition += mov;
//    mColliderComponent.moveBy(mov);
//    mSpriteComponent.moveBy(mov);
//    mHealthComponent.moveBy(mov);
//}