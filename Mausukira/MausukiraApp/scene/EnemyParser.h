#ifndef ENEMYPARSER_H
#define ENEMYPARSER_H

#include "json/value.h"
class EnemySpawner;
class EnemyParser
{
public:
    EnemyParser();
    static void loadEnemies(EnemySpawner& enemySpawner);
    static void parseEnemies(const Json::Value& enemiesJson, unsigned int index,
                             EnemySpawner& enemySpawner);
};


#endif// ENEMYPARSER_H
