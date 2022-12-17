#include "EnemySpawner.h"
#include "RndSpriteComponent.h"
#include "ecs/Entity.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "ecs/components/MovableComponent.h"
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

void EnemySpawner::createEnemy(Scene* scene)
{
    /** First room is reserved for hero character, so iterator++ */
    std::list<Room>::iterator it;
    for (it = scene->mMapContext.mRooms.begin(), ++it; it != scene->mMapContext.mRooms.end(); ++it)
    {
        int numberOfEnemies = generateIntNumberInRange(1, 4);
        for (int i = 0; i < numberOfEnemies; ++i)
        {
            sf::Vector2i enemyLocation = getEnemyMapLocation(it->mGrid, it->mSize);
            generateEnemyEntity(scene, it->mLocation + enemyLocation);
        }
    }
}

sf::Vector2i EnemySpawner::getEnemyMapLocation(Room::RoomGrid& mGrid, const sf::Vector2i& size)
{
    auto [generatedXPos, generatedYPos] = this->genEnemyPosWithinRoom(size);

    if (static_cast<Room::RoomGridType>(mGrid[generatedXPos][generatedYPos]) ==
        Room::RoomGridType::ROOM)
    {
        mGrid[generatedXPos][generatedYPos] = static_cast<int>(Room::RoomGridType::ENEMY);
        return sf::Vector2i(generatedXPos, generatedYPos);
    }
    else
    {
        getEnemyMapLocation(mGrid, size);
    }
}

std::pair<int, int> EnemySpawner::genEnemyPosWithinRoom(const sf::Vector2i& size) const
{
    return std::pair<int, int>(generateIntNumberInRange(0, size.x - 1),
                               generateIntNumberInRange(0, size.y - 1));
}

void EnemySpawner::generateEnemyEntity(Scene* scene, sf::Vector2i position)
{
    EntityStatistic enemyStats = generateStats();
    Entity enemy = {scene->mRegistry.create(), scene};
    enemy.AddComponent<RndSpriteComponent>(mTextureCreator);
    enemy.AddComponent<ColliderComponent>(
        "Enemy", enemy.GetComponent<RndSpriteComponent>().mCurrentSprite.getGlobalBounds());
    enemy.AddComponent<MovableComponent>();
    enemy.AddComponent<HealthComponent>(static_cast<float>(enemyStats.mHealth));
    enemy.AddComponent<TransformComponent>(
        enemy.GetComponent<ColliderComponent>(), enemy.GetComponent<RndSpriteComponent>(),
        enemy.GetComponent<HealthComponent>(),
        sf::Vector2f{static_cast<float>(position.x * TILE_SIZE),
                     static_cast<float>(position.y * TILE_SIZE)});
    enemy.AddComponent<EntityStatistic>(enemyStats);
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

EnemySpawner::EnemySpawner(TextureManager& textureManager)
    : mTextureCreator(textureManager)
{
}
