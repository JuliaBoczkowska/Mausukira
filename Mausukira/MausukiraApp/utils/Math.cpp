#ifndef MATH_H
#define MATH_H

#include "ecs/components/ShootingComponents.h"
#include "dungeon/map/Constants.h"
#include <cstdlib>


inline float distance(const sf::Vector2f v1, const sf::Vector2f& v2)
{
    return std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}

inline float calculateVectorLength(sf::Vector2f vector)
{
    return static_cast<float>(sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
}

inline float getRotationAngleInRadians(const sf::Vector2f& velocity)
{
    return atan2(velocity.x, velocity.y) * (180 / PI);
}

inline void setOrientation(WeaponComponent& weaponComponent, float rotAngle)
{
    weaponComponent.mWeapon.setRotation(180 - rotAngle);
}

inline sf::Vector2f normalizeVector(sf::Vector2f vector)
{
    return vector / calculateVectorLength(vector);
}

inline float setOrientation(float currentOrientation, sf::Vector2f velocity)
{
    if (calculateVectorLength(velocity) > 0)
    {
        return atan2(velocity.x, velocity.y);
    }
    else
    {
        return currentOrientation;
    }
}

sf::Transform rotate(sf::Vector2f& facingVector, sf::Vector2f& sideVector)
{
    // clang-format off
    sf::Transform mat(
        facingVector.x, facingVector.y, 0,
        sideVector.x, sideVector.y, 0,
        0, 0, 1);
    // clang-format on

    return mat;
}

inline sf::Vector2f
localSpaceToWorldSpace(sf::Vector2f& point, sf::Vector2f& facingVector, sf::Vector2f& sideVector,
    sf::Vector2f& position)
{
    //make a copy of the point
    sf::Vector2f TransPoint = point;

    //create a transformation matrix
    sf::Transform matTransform;

    //rotate
    matTransform.combine(rotate(facingVector, sideVector));

    //and translate
    matTransform.translate(facingVector);

    //now transform the vertices
    matTransform.transformPoint(TransPoint);
    return TransPoint;
}
    

#endif //MATH_H
