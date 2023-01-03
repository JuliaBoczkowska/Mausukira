#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "AttackType.h"

class PositionComponent;

class AiComponent
{
    int coverSearchRadius;
    bool playerDetected;
    PositionComponent* mPlayerPosition;
};


#endif //AICOMPONENT_H
