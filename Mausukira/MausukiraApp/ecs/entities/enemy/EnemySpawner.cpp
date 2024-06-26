#include "EnemySpawner.h"
#include "ecs/entities/Entity.h"
#include "ecs/components/MovableComponent.h"
#include "EnemyTypes.h"
#include "ecs/Scene.h"
#include "utils/RandomNumberGenerator.h"

EnemySpawner::EnemySpawner(TextureManager& textureManager)
    : mTextureCreator(textureManager)
{
}

void EnemySpawner::addEnemyInfo(const std::string& name, EnemyModelInfo enemyInfo)
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

void EnemySpawner::addEnemyEntity(Scene* scene)
{
    /** First room is reserved for hero character, so iterator++ */
    std::list<Room>::iterator it;
    for (it = scene->mMapContext->mRooms.begin(), ++it; it != scene->mMapContext->mRooms.end(); ++it)
    {
        int numberOfEnemies = generateIntNumberInRange(1, 4);
        for (int i = 0; i < numberOfEnemies; ++i)
        {
            sf::Vector2i enemyLocation = getEnemyMapLocation(it->mGrid, it->mSize);
            const auto& enemyPosition = it->mLocation + enemyLocation;
            mEnemyEntity.emplace_back(
                std::make_unique<Enemy>(scene, generateStats(), enemyPosition, mTextureCreator.generate()));
        }
    }
    selectEnemyToBeADoorToNextLevel();
}

sf::Vector2i EnemySpawner::getEnemyMapLocation(Room::RoomGrid& mGrid, const sf::Vector2i& size)
{
    auto [generatedXPos, generatedYPos] = genEnemyPosWithinRoom(size);

    if (static_cast<Room::RoomGridType>(mGrid[generatedXPos][generatedYPos]) ==
        Room::RoomGridType::ROOM)
    {
        mGrid[generatedXPos][generatedYPos] = static_cast<int>(Room::RoomGridType::ENEMY);
        return { generatedXPos, generatedYPos };
    }
    return getEnemyMapLocation(mGrid, size);
}

std::pair<int, int> EnemySpawner::genEnemyPosWithinRoom(const sf::Vector2i& size)
{
    return { generateIntNumberInRange(0, size.x - 1),
             generateIntNumberInRange(0, size.y - 1) };
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
    return statsToBeFilled;
}

std::pair<std::string, EnemyModelInfo> EnemySpawner::chooseEnemyModelType()
{
    if (generateIntNumberInRange(1, 3) == 1)
    {
        return { "Shooting_Zombie", mEnemyTypes.find(EnemyType::Shooting_Zombie)->second };
    }
    else
    {
        return { "Walking_Zombie", mEnemyTypes.find(EnemyType::Walking_Zombie)->second };
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

void EnemySpawner::selectEnemyToBeADoorToNextLevel()
{

    auto randomEnemy = mEnemyEntity.at(generateIntNumberInRange(0, mEnemyEntity.size() - 1)).get();
    auto& entityStatistic = randomEnemy->enemy.getComponent<EntityStatistic>();

    entityStatistic.isTransitionToNextLevel = true;
}
