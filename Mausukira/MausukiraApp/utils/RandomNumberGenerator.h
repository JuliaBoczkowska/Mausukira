#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include "SFML/System/Vector2.hpp"
#include <random>

static std::random_device dev;///< It produces high quality unsigned integer random numbers. (engine
                              ///< based on Mersenne Twister algorithm)
static std::mt19937 engine(dev());///< A random number generator. It is used to seed engine.

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

static sf::Vector2i generateTwoIntNumbersInRange(const auto& minSize, const auto& maxSize)
{
    const std::uniform_int_distribution<int> generatePosHeight(minSize, maxSize);
    const std::uniform_int_distribution<int> generatePosWidth(minSize, maxSize);

    return sf::Vector2i{generatePosWidth(engine), generatePosHeight(engine)};
}

#endif// RANDOMNUMBERGENERATOR_H
