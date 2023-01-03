#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "AttackType.h"

class PositionComponent;

struct AiComponent
{
    int coverSearchRadius;
    bool playerDetected;
    PositionComponent* mPlayerPositionComponent;
};


#endif //AICOMPONENT_H
