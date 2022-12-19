#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H
#include "System.h"

class ScoreSystem : public System
{
public:
    ScoreSystem(entt::registry& registry);
    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
};


#endif// SCORESYSTEM_H
