#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include "System.h"

class ScoreSystem : public System
{
public:
    ScoreSystem(entt::registry& registry);
    
    void update(const sf::Time& dt) override;
};


#endif// SCORESYSTEM_H
