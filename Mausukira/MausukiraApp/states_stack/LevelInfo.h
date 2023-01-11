#ifndef LEVELINFO_H
#define LEVELINFO_H

struct LevelInfo
{
    int levelNumber{};
    int changeNextLevel{false};
    int score{0};
    int playerHealth{20};
};

#endif// LEVELINFO_H
