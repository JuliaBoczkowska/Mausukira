#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.h"
#include "EnemyTextureGenerator.h"
#include "EnemyTypes.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "ecs/components/EntityComponent.h"
#include "utils/TextureManager.h"
#include "dungeon/map/room/Room.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>

class Scene;

class EnemySpawner
{
public:
    EnemySpawner(TextureManager& textureManager);

    void addEnemyInfo(const std::string& name, EnemyModelInfo enemyInfo);

    void addEnemyEntity(Scene* scene);

private:
    EntityStatistic generateStats();

    static int rndGenerateHealth(EnemyModelInfo& generationConfig);

    static float rndGenerateAttackDamage(EnemyModelInfo& generationConfig);

    static float rndGenerateAttackSpeed(EnemyModelInfo& generationConfig);

    static float rndGenerateMovementSpeed(EnemyModelInfo& generationConfig);

    sf::Vector2i getEnemyMapLocation(Room::RoomGrid& mGrid, const sf::Vector2i& size);

    static std::pair<int, int> genEnemyPosWithinRoom(const sf::Vector2i& size);

    std::pair<std::string, EnemyModelInfo> chooseEnemyModelType();

    void selectEnemyToBeADoorToNextLevel();

private:
    std::map<EnemyType, EnemyModelInfo> mEnemyTypes;
    EnemyTextureGenerator mTextureCreator;
    std::vector<std::unique_ptr<Enemy>> mEnemyEntity;
};

#endif// ENEMYSPAWNER_H
