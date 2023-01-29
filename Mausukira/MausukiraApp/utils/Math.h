#ifndef MATH_H
#define MATH_H

#include "dungeon/map/Constants.h"
#include "ecs/components/ShootingComponents.h"
#include <cstdlib>

float calculateVectorLength(sf::Vector2f vector);

float getRotationAngleInRadians(const sf::Vector2f& velocity);

void setOrientation(WeaponComponent& weaponComponent, float rotAngle);

sf::Vector2f normalizeVector(sf::Vector2f vector);

[[maybe_unused]] float setOrientation(float currentOrientation, sf::Vector2f velocity);

[[maybe_unused]] sf::Transform rotate(sf::Vector2f& facingVector, sf::Vector2f& sideVector);

sf::Vector2f localSpaceToWorldSpace(sf::Vector2f& point, sf::Vector2f& facingVector,
                                    sf::Vector2f& sideVector, sf::Vector2f& position);

sf::Vector2f perpendicular(sf::Vector2f v);

sf::Vector2f truncate(sf::Vector2f velocity, float maxSpeed);

sf::Vector2f rotateBy(float angle, sf::Vector2f vector);

float calculateVectorsLength(sf::Vector2f begin, sf::Vector2f end);

float perpendicularDotProduct(const sf::Vector2f& a, const sf::Vector2f& b);

float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b);

bool lineIntersectsRectangle(const sf::FloatRect& rect, const sf::Vector2f& vectorA,
                             const sf::Vector2f& vectorB);
bool LineCollision(const sf::Vector2f& A1, const sf::Vector2f& A2, const sf::Vector2f& B1,
                   const sf::Vector2f& B2, sf::Vector2f* out);
#endif// MATH_H
