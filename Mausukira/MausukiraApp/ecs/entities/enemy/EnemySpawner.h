#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.h"
#include "EnemyTextureGenerator.h"
#include "EnemyTypes.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "dungeon/map/room/Room.h"
#include <map>
#include <string>

class Scene;
class TextureManager;
class EnemySpawner
{
public:
    EnemySpawner(TextureManager& textureManager);

    void addEnemyInfo(const std::string& name, EnemyModelInfo enemyInfo);

    void addEnemyEntity(Scene* scene);

private:
    EntityStatistic generateStats();

    sf::Vector2i getEnemyMapLocation(Room::RoomGrid& mGrid, const sf::Vector2i& size);

    static std::pair<int, int> genEnemyPosWithinRoom(const sf::Vector2i& size);

    std::pair<std::string, EnemyModelInfo> chooseEnemyModelType();

    void selectEnemyToBeADoorToNextLevel();

public:
    std::vector<std::unique_ptr<Enemy>> mEnemyEntity;

private:
    std::map<EnemyType, EnemyModelInfo> mEnemyTypes;
    EnemyTextureGenerator mTextureCreator;
};

#endif// ENEMYSPAWNER_H
