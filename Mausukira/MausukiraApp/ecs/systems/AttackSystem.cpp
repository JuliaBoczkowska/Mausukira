#include "AttackSystem.h"
#include "ecs/components/PlayerComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/PositionComponent.h"

AttackSystem::AttackSystem(entt::registry& registry, SharedContext& sharedContext)
    : System(registry)
    , mRenderWindow(sharedContext.window())
{
}

void AttackSystem::handleInput(sf::Event& event)
{
}

void AttackSystem::normalizeDirectionalVector()
{
    mAimDirectionNormalized = mAimDirection / calculateVectorLength();
}

float AttackSystem::calculateVectorLength() const
{
    return static_cast<float>(sqrt(pow(mAimDirection.x, 2) + pow(mAimDirection.y, 2)));
}

void AttackSystem::update(const sf::Time& dt)
{
    calcDirectionalNormalizedVector();
    updateProjectiles(dt);
    shootNewProjectile();
}

void AttackSystem::shootNewProjectile()
{
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//    {
//        mRegistry.view<Weapon>().each(
//            [&](Weapon& weapon)
//            {
//                weapon.shoot(mPlayerCenter, mAimDirectionNormalized);
//            });
//    }
}

void AttackSystem::updateProjectiles(const sf::Time& dt)
{
//    mRegistry.view<Weapon>().each(
//        [&](Weapon& weapon)
//        {
//            weapon.update(dt);
//        });
}

void AttackSystem::calcDirectionalNormalizedVector()
{
    mRegistry.view<PlayerComponent, PositionComponent>().each(
        [&](PlayerComponent& playerComponent, auto& positionComponent)
        {
            mPlayerCenter = positionComponent.mPosition;
        });

    mMouseCoordinates = mRenderWindow.mapPixelToCoords((sf::Mouse::getPosition(mRenderWindow)));
    mAimDirection = mMouseCoordinates - mPlayerCenter;
    normalizeDirectionalVector();
}

void AttackSystem::draw(sf::RenderWindow& window)
{
//    mRegistry.view<Weapon>().each(
//        [&](Weapon& weapon)
//        {
//            weapon.draw(window);
//        });
}
