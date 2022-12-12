#include "EnemySpawner.h"
#include "ecs/Entity.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/MovableComponent.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/enemy/EnemyTypes.h"
#include "scene/Scene.h"
#include "utils/RandomNumberGenerator.h"

void EnemySpawner::addEnemyInfo(std::string name, EnemyModelInfo enemyInfo)
{
    if (name == "Walking_Zombie")
    {
        mEnemyTypes.insert(std::make_pair(EnemyType::Walking_Zombie, std::move(enemyInfo)));
    }
    else
    {
        mEnemyTypes.insert(std::make_pair(EnemyType::Shooting_Zombie, std::move(enemyInfo)));
    }
}

void EnemySpawner::createEnemy(Scene* scene, sf::Sprite sprite)
{
    static float i = 32;
    EntityStatistic enemyStats = generateStats();

    Entity enemy = {scene->mRegistry.create(), scene};
    enemy.AddComponent<ColliderComponent>(
        "Enemy", CollisionBox{sprite.getGlobalBounds(), CollisionBox::COLLISION_TYPE::FOOT});
    enemy.AddComponent<MovableComponent>();
    enemy.AddComponent<HealthComponent>(static_cast<float>(enemyStats.mHealth));
    enemy.AddComponent<SpriteComponent>(sprite);
    enemy.AddComponent<TransformComponent>(
        enemy.GetComponent<ColliderComponent>(), enemy.GetComponent<SpriteComponent>(),
        enemy.GetComponent<HealthComponent>(), sf::Vector2f{i, 0});
    enemy.AddComponent<EntityStatistic>(enemyStats);
    i += 32;
}

EntityStatistic EnemySpawner::generateStats()
{
    auto [nameTag, enemyModel] = chooseEnemyModelType();
    EnemyModelInfo generationConfig = enemyModel;
    EntityStatistic statsToBeFilled;

    statsToBeFilled.mNameTag = nameTag;
    statsToBeFilled.mReactionTime = generationConfig.reactionTime;
    statsToBeFilled.mAttackType = generationConfig.mAttackInfo.attackType;
    statsToBeFilled.mHealth = rndGenerateHealth(generationConfig);
    statsToBeFilled.mAttackDamage = rndGenerateAttackDamage(generationConfig);
    statsToBeFilled.mAttackSpeed = rndGenerateAttackSpeed(generationConfig);
    statsToBeFilled.mMovementSpeed = rndGenerateMovementSpeed(generationConfig);
    statsToBeFilled.hit = []()
    {
        std::cout << "HIT" << std::endl;
    };

    return statsToBeFilled;
}

std::pair<std::string, EnemyModelInfo> EnemySpawner::chooseEnemyModelType()
{
    if (generateIntNumberInRange(1, 3) == 1)
    {
        return std::pair<std::string, EnemyModelInfo>(
            "Shooting_Zombie", mEnemyTypes.find(EnemyType::Shooting_Zombie)->second);
    }
    else
    {
        return std::pair<std::string, EnemyModelInfo>(
            "Walking_Zombie", mEnemyTypes.find(EnemyType::Walking_Zombie)->second);
    }
}

int EnemySpawner::rndGenerateHealth(EnemyModelInfo& generationConfig)
{
    return generateIntNumberInRange(generationConfig.healthMinMax);
}

float EnemySpawner::rndGenerateAttackDamage(EnemyModelInfo& generationConfig)
{
    return generateFloatNumberInRange(generationConfig.mAttackInfo.attackDamageMinMax);
}

float EnemySpawner::rndGenerateAttackSpeed(EnemyModelInfo& generationConfig)
{
    return generateFloatNumberInRange(generationConfig.mAttackInfo.attackSpeedMinMax);
}

float EnemySpawner::rndGenerateMovementSpeed(EnemyModelInfo& generationConfig)
{
    return generateFloatNumberInRange(generationConfig.movementSpeedMinMax);
}