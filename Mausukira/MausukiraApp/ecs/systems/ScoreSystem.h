#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include "System.h"
#include "states_stack/SharedContext.h"

class ScoreSystem : public System
{
public:
    ScoreSystem(entt::registry& registry,  SharedContext& sharedContext);
    
    void update(const sf::Time& dt) override;

    SharedContext& mSharedContext;
};


#endif// SCORESYSTEM_H
