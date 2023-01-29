#include "SteeringBehaviourComponent.h"

bool isFlagOn(int& mBehaviourFlag, EnemyBehaviour enemyBehaviourFlag)
{
    return (mBehaviourFlag & enemyBehaviourFlag) == enemyBehaviourFlag;
}

void setFlagOn(int& mBehaviourFlag, EnemyBehaviour behaviourType)
{
    mBehaviourFlag |= behaviourType;
}

void clearFlag(int& mBehaviourFlag)
{
    mBehaviourFlag = 0x00000;
}