#include "EnemyParser.h"
#include "EnemySpawner.h"
#include <fstream>
#include <iostream>
#include "json/json.h"
#include <unordered_map>

void EnemyParser::loadEnemies(EnemySpawner& enemySpawner)
{
    Json::Value enemiesJson;
    std::ifstream file("resources/tiles/enemies.json", std::ifstream::binary);
    try
    {
        if (file.fail())
        {
            throw std::runtime_error("ERR: EnemyParser::loadEnemies - No enemies.json file exists");
        }
        file >> enemiesJson;
        for (Json::Value::ArrayIndex index = 0; index != enemiesJson.size(); index++)
        {
            parseEnemies(enemiesJson, index, enemySpawner);
        }
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void EnemyParser::parseEnemies(const Json::Value& enemiesJson, unsigned int index,
    EnemySpawner& enemySpawner)
{
    std::string name = enemiesJson[index]["Name"].asString();
    int attackType = enemiesJson[index]["AttackType"].asInt();

    auto attackDamage = enemiesJson[index]["AttackDamage"];
    auto attackDamageMinMax =
        sf::Vector2f(attackDamage["min"].asFloat(), attackDamage["max"].asFloat());

    auto health = enemiesJson[index]["Health"];
    auto healthMinMax = sf::Vector2i(health["min"].asInt(), health["max"].asInt());

    auto attackSpeed = enemiesJson[index]["Attack_Speed"];
    auto attackSpeedMinMax =
        sf::Vector2f(attackSpeed["min"].asFloat(), attackSpeed["max"].asFloat());

    auto movementSpeed = enemiesJson[index]["Movement_Speed"];
    auto movementSpeedMinMax =
        sf::Vector2f(movementSpeed["min"].asFloat(), movementSpeed["max"].asFloat());

    auto reactionTime = enemiesJson[index]["Reaction_Time"].asFloat();

    EnemyModelInfo enemyStats{
        name,
        AttackInfo{ static_cast<AttackType>(attackType), attackDamageMinMax, attackSpeedMinMax },
        healthMinMax, movementSpeedMinMax, reactionTime };

    enemySpawner.addEnemyInfo(name, enemyStats);
}
