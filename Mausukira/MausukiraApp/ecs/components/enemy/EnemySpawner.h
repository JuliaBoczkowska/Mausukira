#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H
#include "Enemy.h"
#include "EnemyTypes.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "ecs/components/EntityComponent.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>

class Scene;
class EnemySpawner
{
public:
    EnemySpawner() = default;

    void addEnemyInfo(std::string name, EnemyModelInfo enemyInfo);
    void createEnemy(Scene* scene, sf::Sprite sprite);

private:
    EntityStatistic generateStats();
    int rndGenerateHealth(EnemyModelInfo& generationConfig);
    float rndGenerateAttackDamage(EnemyModelInfo& generationConfig);
    float rndGenerateAttackSpeed(EnemyModelInfo& generationConfig);
    float rndGenerateMovementSpeed(EnemyModelInfo& generationConfig);
    std::pair<std::string, EnemyModelInfo> chooseEnemyModelType();

private:
    std::map<EnemyType, EnemyModelInfo> mEnemyTypes;
};

#endif// ENEMYSPAWNER_H
