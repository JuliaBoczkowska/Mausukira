#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include "SFML/System/Vector2.hpp"
#include <random>

/** Used seed, produces high quality unsigned integer random numbers. */
static std::random_device seed;
/** Random number generator. */
static std::mt19937 engine(seed());

static float generateFloatNumberInRange(const float& minSize, const float& maxSize)
{
    std::uniform_real_distribution<float> generateNum(minSize, maxSize);
    return generateNum(engine);
}

static float generateIntNumberInRange(const float& minSize, const float& maxSize)
{
    std::uniform_int_distribution<int> generateNum(minSize, maxSize);
    return generateNum(engine);
}

static float generateIntNumberInRange(const sf::Vector2i& range)
{
    std::uniform_int_distribution<int> generateNum(range.x, range.y);
    return generateNum(engine);
}

static float generateFloatNumberInRange(const sf::Vector2f& range)
{
    std::uniform_real_distribution<float> generateNum(range.x, range.y);
    return generateNum(engine);
}

static sf::Vector2i generateTwoIntNumbersInRange(const auto& minSize, const auto& maxSize)
{
    const std::uniform_int_distribution<int> generatePosHeight(minSize, maxSize);
    const std::uniform_int_distribution<int> generatePosWidth(minSize, maxSize);

    return sf::Vector2i{generatePosWidth(engine), generatePosHeight(engine)};
}

#endif// RANDOMNUMBERGENERATOR_H
