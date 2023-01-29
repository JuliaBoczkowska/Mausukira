#include "CameraSystem.h"
#include "states_stack/SharedContext.h"

CameraSystem::CameraSystem(entt::registry& registry, SharedContext& sharedContext,
                           MapContext& mapContext, sf::View& view)
    : System(registry)
    , mSharedContext(sharedContext)
    , mWindow(sharedContext.window.mRenderWindow)
    , mCameraView(view)
{
    setInitialPlayerPosition(mapContext);
    mWindow.setView(mWindow.getDefaultView());
}

void CameraSystem::setInitialPlayerPosition(const MapContext& mapContext)
{
    mCameraView.setCenter(mapContext.mCenterOfTheFirstRoom.x, mapContext.mCenterOfTheFirstRoom.y);
    cameraSetView();
    updateBackground();
}

void CameraSystem::update(const sf::Time& dt)
{
    moveViewWithMiddleMouseButton();
    updateCamera();
}

void CameraSystem::updateCamera()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        mRegistry.view<PositionComponent>().each(
            [&](PositionComponent& positionComponent)
            {
                followPlayer(positionComponent.mPosition);
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

void CameraSystem::followPlayer(const sf::Vector2f& position)
{
    mCameraView.setCenter(position);
    cameraSetView();
}

void CameraSystem::cameraSetView()
{
    mWindow.setView(mCameraView);
}

void CameraSystem::moveViewWithMiddleMouseButton()
{
    static auto oldCoordsOfMouse = sf::Mouse::getPosition();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        const auto newCoordsOfMouse = sf::Mouse::getPosition();
        moveViewRelativeToMouseCoords(oldCoordsOfMouse, newCoordsOfMouse);
        updateBackground();
    }
    oldCoordsOfMouse = sf::Mouse::getPosition();
}

void CameraSystem::moveViewRelativeToMouseCoords(const sf::Vector2i& oldCoordsOfMouse,
                                                 const sf::Vector2i& newCoordsOfMouse)
{
    mCameraView.move(mWindow.mapPixelToCoords(oldCoordsOfMouse) -
                     mWindow.mapPixelToCoords(newCoordsOfMouse));
    mWindow.setView(mCameraView);
}

void CameraSystem::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        const auto oldCoordsOfMouse{getCursorCoordinates(event)};
        zoomInAndOut(event);
        cameraSetView();

        const auto newCoordsOfMouse{getCursorCoordinates(event)};
        zoomIntoMouseCursor(oldCoordsOfMouse, newCoordsOfMouse);
        updateBackground();
    }
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
    const auto maxZoom = mWindow.getDefaultView().getSize().x * 2.f;
    const auto minZoom = mWindow.getDefaultView().getSize().x / 2.f;

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
