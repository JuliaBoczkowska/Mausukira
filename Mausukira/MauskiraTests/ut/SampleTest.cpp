#include "dungeon/CollisionBox.h"
#include "gtest/gtest.h"

namespace
{
// Tests the Increment() method.

TEST(TwojaStaraTest, TestDupsztala)
{
    auto dupsztal = true;
    EXPECT_TRUE(dupsztal);
}

TEST(TwojaStaraTest, RuchanieBox)
{
    sf::FloatRect erekciarz(0, 0, 10, 10);
    CollisionBox sutek;

    auto result = sutek.setupCollider(erekciarz);
    EXPECT_EQ(result.getOutlineColor(), sf::Color::Red);
    EXPECT_NE(result.getOutlineThickness(), 0);
}

TEST(TwojaStaraTest, SprawdzStopki)
{
    EXPECT_EQ(CollisionBox::FOOT_ORIGIN_X, -12);
}

}// namespace