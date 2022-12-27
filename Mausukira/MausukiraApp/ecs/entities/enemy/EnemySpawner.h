#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.h"
#include "EnemyTextureGenerator.h"
#include "EnemyTypes.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "ecs/components/EntityComponent.h"
#include "utils/TextureManager.h"
#include "dungeon/map/Room.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>

class Scene;

class EnemySpawner
{
    const int TILE_SIZE = 32;

public:
    EnemySpawner(TextureManager& textureManager);

    void addEnemyInfo(std::string name, EnemyModelInfo enemyInfo);

    void addEnemyEntity(Scene* scene);

private:
    EntityStatistic generateStats();

    int rndGenerateHealth(EnemyModelInfo& generationConfig);

    float rndGenerateAttackDamage(EnemyModelInfo& generationConfig);

    float rndGenerateAttackSpeed(EnemyModelInfo& generationConfig);

    float rndGenerateMovementSpeed(EnemyModelInfo& generationConfig);

    sf::Vector2i getEnemyMapLocation(Room::RoomGrid& mGrid, const sf::Vector2i& size);

    std::pair<int, int> genEnemyPosWithinRoom(const sf::Vector2i& size) const;

    std::pair<std::string, EnemyModelInfo> chooseEnemyModelType();

private:
    std::map<EnemyType, EnemyModelInfo> mEnemyTypes;
    EnemyTextureGenerator mTextureCreator;
    std::vector<std::unique_ptr<Enemy>> mEnemyEntity;
};

#endif// ENEMYSPAWNER_H