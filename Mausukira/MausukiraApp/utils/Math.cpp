#include "Math.h"

float calculateVectorLength(sf::Vector2f vector)
{
    return static_cast<float>(sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
}

float calculateVectorsLength(sf::Vector2f begin, sf::Vector2f end)
{
    return static_cast<float>(sqrt(pow(end.x - begin.x, 2) + pow(end.y - begin.y, 2)));
}

float getRotationAngleInRadians(const sf::Vector2f& velocity)
{
    return atan2(velocity.x, velocity.y) * (180 / PI);
}

sf::Vector2f normalizeVector(sf::Vector2f vector)
{
    return vector / calculateVectorLength(vector);
}

[[maybe_unused]] float setOrientation(float currentOrientation, sf::Vector2f velocity)
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

[[maybe_unused]] sf::Transform rotate(sf::Vector2f& facingVector, sf::Vector2f& sideVector)
{
    //    sf::Transform temp{0, 0, 0, 0, 0, 0, 0, 0, 0};
    sf::Transform temp;
    // clang-format off
    sf::Transform mat(
        facingVector.x, facingVector.y, 0,
        sideVector.x, sideVector.y, 0,
        0, 0, 1);
    // clang-format on

    mat.combine(temp);
    return mat;
}

sf::Vector2f localSpaceToWorldSpace(sf::Vector2f& point, sf::Vector2f& facingVector,
                                    sf::Vector2f& sideVector, sf::Vector2f& position)
{
    // make a copy of the point
    sf::Vector2f TransPoint = point;

    // create a transformation matrix
    sf::Transform matTransform;

    // rotate
    rotate(facingVector, sideVector);

    // and translate
    matTransform.translate(position);

    // now transform the vertices
    TransPoint = matTransform.transformPoint(TransPoint);
    return TransPoint;
}

sf::Vector2f perpendicular(sf::Vector2f v)
{
    return sf::Vector2f(-v.y, v.x);
}

sf::Vector2f truncate(sf::Vector2f velocity, float maxSpeed)
{
    if (calculateVectorLength(velocity) > maxSpeed)
    {
        velocity = normalizeVector(velocity);
    }
    return velocity;
}

sf::Vector2f rotateBy(float angle, sf::Vector2f vector)
{
    sf::Transform rotationMatrix;
    rotationMatrix.rotate(angle);
    return rotationMatrix.transformPoint(vector);
}
float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return (a.x * b.x) + (a.y * b.y);
}
float perpendicularDotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return (a.y * b.x) - (a.x * b.y);
}

bool lineIntersectsRectangle(const sf::FloatRect& rect, const sf::Vector2f& vectorA,
                             const sf::Vector2f& vectorB)
{
    // Find min and max X for the segment
    auto minX = std::min(vectorA.x, vectorB.x);
    auto maxX = std::max(vectorA.x, vectorB.x);

    // Find the intersection of the segment's and rectangle's x-projections
    if (maxX > rect.left + rect.width)
    {
        maxX = rect.left + rect.width;
    }

    if (minX < rect.left)
    {
        minX = rect.left;
    }

    // If Y-projections do not intersect then there's no intersection
    if (minX > maxX)
    {
        return false;
    }

    // Find corresponding min and max Y for min and max X we found before
    auto minY = vectorA.y;
    auto maxY = vectorB.y;

    auto dx = vectorB.x - vectorA.x;
    if (std::abs(dx) > 0.0000001f)
    {
        auto k = (vectorB.y - vectorA.y) / dx;
        auto b = vectorA.y - k * vectorA.x;
        minY = k * minX + b;
        maxY = k * maxX + b;
    }

    if (minY > maxY)
    {
        std::swap(minY, maxY);
    }

    // Find the intersection of the line and rectangle's y-projections
    if (maxY > rect.top + rect.height)
    {
        maxY = rect.top + rect.height;
    }

    if (minY < rect.top)
    {
        minY = rect.top;
    }

    // If Y-projections do not intersect then there's no intersection
    if (minY > maxY)
    {
        return false;
    }
    return true;
}

bool LineCollision(const sf::Vector2f& A1, const sf::Vector2f& A2, const sf::Vector2f& B1,
                   const sf::Vector2f& B2, sf::Vector2f* out)
{
    sf::Vector2f a(A2 - A1);
    sf::Vector2f b(B2 - B1);
    sf::Vector2f c(B2 - A2);

    float f = perpendicularDotProduct(a, b);

    // lines are parallel
    if (!f)
    {
        return false;
    }

    float aa = perpendicularDotProduct(a, c);
    float bb = perpendicularDotProduct(b, c);

    if (f < 0)
    {
        if (aa > 0)
        {
            return false;
        }
        if (bb > 0)
        {
            return false;
        }
        if (aa < f)
        {
            return false;
        }
        if (bb < f)
        {
            return false;
        }
    }
    else
    {
        if (aa < 0)
        {
            return false;
        }
        if (bb < 0)
        {
            return false;
        }
        if (aa > f)
        {
            return false;
        }
        if (bb > f)
        {
            return false;
        }
    }

    if (out)
    {
        *out = b * (1.0f - (aa / f)) + B1;
    }// assigns the point of intersection

    return true;
}
