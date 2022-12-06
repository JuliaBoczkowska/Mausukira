#include "RenderingSystem.h"
#include "../components/SpriteComponent.h"
#include "ecs/components/ColliderComponent.h"

RenderingSystem::RenderingSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
{
}

void RenderingSystem::handleInput(sf::Event& event)
{
    sortSprites();
}

void RenderingSystem::sortSprites()
{
    mRegistry.sort<SpriteComponent>(
        [this](const SpriteComponent& lhs, const SpriteComponent& rhs)
        {
            auto lhsPos = lhs.mCurrentSprite.getPosition();
            auto rhsPos = rhs.mCurrentSprite.getPosition();

            if (lhs.mLayer == rhs.mLayer)
            {
                return lhsPos.y < rhsPos.y;
            }
            return lhs.mLayer < rhs.mLayer;
        });
}

void RenderingSystem::update(const sf::Time& dt)
{
}


void RenderingSystem::draw(sf::RenderWindow& window)
{
    mRegistry.view<SpriteComponent, ColliderComponent>().each(
        [&](SpriteComponent& spriteComponent, ColliderComponent& colliderComponent)
        {
            spriteComponent.draw(window);
            colliderComponent.draw(window);
        });

    // sf::FloatRect Window::GetViewSpace(){
    //  sf::Vector2f viewCenter = m_window.getView().getCenter();
    //  sf::Vector2f viewSize = m_window.getView().getSize();
    //  sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
    //  sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    //  return viewSpace;
    // }

    //            if (!window.GetViewSpace().intersects(
    //                    spriteComponent.mCurrentSprite.getGlobalBounds()))
    //            {
    //                return;
    //            }
}
