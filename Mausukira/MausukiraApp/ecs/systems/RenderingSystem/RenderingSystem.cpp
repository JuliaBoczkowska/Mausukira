#include "RenderingSystem.h"
#include "dungeon/Debug.h"
#include "ecs/components/AiComponent.h"
#include "ecs/components/Components.h"
#include "ecs/components/SteeringBehaviourComponent.h"


RenderingSystem::RenderingSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{
}

void RenderingSystem::draw(sf::RenderWindow& window)
{
    mRegistry.view<HealthComponent>().each(
        [&](HealthComponent& healthComponent)
        {
            window.draw(healthComponent.mHealthBarOutline);
            window.draw(healthComponent.mHealthBarRect);
        });

    mRegistry.view<SpriteComponent>().each(
        [&](SpriteComponent& spriteComponent)
        {
            for (const auto& sprite: spriteComponent.mSprites)
            {
                window.draw(sprite);
            }
        });

    mRegistry.view<ColliderComponent>().each(
        [&](ColliderComponent& colliderComponent)
        {
            //            window.draw(colliderComponent.mRectangle);
        });

    mRegistry.view<ProjectileBody>().each(
        [&](ProjectileBody& projectileBody)
        {
            window.draw(projectileBody.mProjectile);
        });

    mRegistry.view<WeaponComponent>().each(
        [&](WeaponComponent& weaponComponent)
        {
            window.draw(weaponComponent.mWeapon);
        });

    mRegistry.view<ScoreComponent>().each(
        [&](ScoreComponent& scoreComponent)
        {
            auto oldView = window.getView();
            window.setView(window.getDefaultView());
            window.draw(scoreComponent.counter);
            window.draw(scoreComponent.mLevelNumber);
            window.draw(scoreComponent.rectangle);

            window.setView(oldView);
        });

    mRegistry.view<DoorBodyComponent>().each(
        [&](DoorBodyComponent& doorBodyComponent)
        {
            window.draw(doorBodyComponent.mDoorSprite);
        });

    mRegistry.view<SensorComponent, VelocityComponent, PositionComponent>().each(
        [&](SensorComponent& sensorComponent, VelocityComponent velocityComponent,
            PositionComponent& positionComponent)
        {
            if (debug::DEBUG_AI)
            {
                sf::VertexArray line(sf::Lines, 2);
                line[0].position = sensorComponent.lineOfSight.front();
                line[0].color = sf::Color::Cyan;
                line[1].position = sensorComponent.lineOfSight.back();
                line[1].color = sf::Color::Cyan;
                window.draw(line);
            }
        });

    mRegistry.view<SteeringBehaviourComponent, PositionComponent>().each(
        [&](SteeringBehaviourComponent& steeringBehaviourComponent,
            PositionComponent& positionComponent)
        {
            if (debug::DEBUG_AI)
            {
                auto positionAlignedToEnemyCenter = sf::Vector2f{
                    positionComponent.mPosition.x + 16, positionComponent.mPosition.y + 16};
                for (const auto& whisker: steeringBehaviourComponent.whiskers)
                {

                    sf::VertexArray line(sf::Lines, 2);
                    line[0].position = whisker;
                    line[0].color = sf::Color::Blue;
                    line[1].position = positionAlignedToEnemyCenter;
                    line[1].color = sf::Color::Blue;
                    window.draw(line);
                }

                sf::VertexArray line(sf::Lines, 2);
                line[0].position = steeringBehaviourComponent.normal.first;
                line[0].color = sf::Color::Cyan;
                line[1].position = steeringBehaviourComponent.normal.second;
                line[1].color = sf::Color::Cyan;
                window.draw(line);

                sf::CircleShape circle;
                circle.setRadius(2);
                circle.setFillColor(sf::Color::Yellow);
                circle.setPosition(steeringBehaviourComponent.newPoint);
                window.draw(circle);
            }
        });
}
