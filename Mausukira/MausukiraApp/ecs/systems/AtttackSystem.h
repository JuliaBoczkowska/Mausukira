#ifndef ATTTACKSYSTEM_H
#define ATTTACKSYSTEM_H
#include "System.h"
#include "states_stack/SharedContext.h"

class AttackSystem : public System
{
public:
    AttackSystem(entt::registry& registry, SharedContext& sharedContext);
    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    float calculateVectorLength() const;
    void normalizeDirectionalVector();
    void calcDirectionalNormalizedVector();
    void updateProjectilesPosition(const sf::Time& dt);
    void shootNewProjectile();

private:
    sf::Vector2f mMouseCoordinates{};
    sf::Vector2f mAimDirection{};
    sf::Vector2f mAimDirectionNormalized{};
    sf::Vector2f mPlayerCenter{};

    sf::RenderWindow& mRenderWindow;
};


#endif// ATTTACKSYSTEM_H
