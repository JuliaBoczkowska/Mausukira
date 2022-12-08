#include "CameraSystem.h"
#include "ecs/components/TransformComponent.h"
#include "states_stack/SharedContext.h"

CameraSystem::CameraSystem(entt::registry& registry, SharedContext& sharedContext)
    : System(registry)
    , mSharedContext(sharedContext)
    , mWindow(sharedContext.window.mRenderWindow)
{
    mCameraView.zoom(0.6);
}

void CameraSystem::update(const sf::Time& dt)
{
    updateCamera();
}

void CameraSystem::updateCamera()
{
    if (!mHandlesZoom)
    {
        mRegistry.view<TransformComponent>().each(
            [&](TransformComponent& transformComponent)
            {
                followPlayer(transformComponent);
                updateBackground();
            });
    }
}
void CameraSystem::updateBackground()
{
    mSharedContext.background.setTextureRect(
        sf::IntRect(0, 0, static_cast<int>(mCameraView.getSize().x),
                    static_cast<int>(mCameraView.getSize().y)));
    mSharedContext.background.setPosition(mWindow.mapPixelToCoords({0, 0}));
}

void CameraSystem::followPlayer(const TransformComponent& transformComponent)
{
    mCameraView.setCenter(transformComponent());
    cameraSetView();
}

void CameraSystem::cameraSetView()
{
    mWindow.setView(mCameraView);
}

void CameraSystem::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        mHandlesZoom = true;

        const auto oldCoordsOfMouse{getCursorCoordinates(event)};
        zoomInAndOut(event);
        cameraSetView();

        const auto newCoordsOfMouse{getCursorCoordinates(event)};
        zoomIntoMouseCursor(oldCoordsOfMouse, newCoordsOfMouse);
        updateBackground();
    }
    mHandlesZoom = false;
}

sf::Vector2f CameraSystem::getCursorCoordinates(const sf::Event& event) const
{
    return mWindow.mapPixelToCoords({event.mouseWheelScroll.x, event.mouseWheelScroll.y});
}

void CameraSystem::zoomIntoMouseCursor(const sf::Vector2f& oldCoordsOfMouse,
                                       const sf::Vector2f& newCoordsOfMouse)
{
    /** Prevents zooming into center of window */
    mCameraView.move({oldCoordsOfMouse - newCoordsOfMouse});
    mWindow.setView(mCameraView);
}

void CameraSystem::zoomInAndOut(const sf::Event& event)
{
    const auto currentZoom = mCameraView.getSize().x;
    const auto maxZoom = mWindow.getDefaultView().getSize().x;
    const auto minZoom = mWindow.getDefaultView().getSize().x / 3.f;

    if (event.mouseWheelScroll.delta > 0)
    {
        zoomIn(currentZoom, minZoom);
    }
    else
    {
        zoomOut(currentZoom, maxZoom);
    }
}

void CameraSystem::zoomOut(const float currentZoom, const float maxZoom)
{
    if (currentZoom < maxZoom)
    {
        mCameraView.zoom(1.1f);
    }
}

void CameraSystem::zoomIn(const float currentZoom, const float minZoom)
{
    if (currentZoom > minZoom)
    {
        mCameraView.zoom(0.9f);
    }
}

void CameraSystem::draw(sf::RenderWindow& window)
{
}
