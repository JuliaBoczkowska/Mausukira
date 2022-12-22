#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "SFML/Graphics/Sprite.hpp"
#include "System.h"
#include "Window.h"
#include "ecs/components/PositionComponent.h"
#include "dungeon/map/MapContext.h"

class SharedContext;

class CameraSystem : public System
{
public:
    CameraSystem(entt::registry& registry, SharedContext& sharedContext, MapContext& mapContext);

    void handleInput(sf::Event& event) override;

    void update(const sf::Time& dt) override;

    void draw(sf::RenderWindow& window) override;

private:
    void updateCamera();

    void cameraSetView();

    void followPlayer(const sf::Vector2f& position);

    void updateBackground();

    void zoomInAndOut(const sf::Event& event);

    void zoomIntoMouseCursor(const sf::Vector2f& oldCoordsOfMouse,
        const sf::Vector2f& newCoordsOfMouse);

    void setInitialPlayerPosition(const MapContext& mapContext);

    sf::Vector2f getCursorCoordinates(const sf::Event& event) const;

    void zoomIn(const float currentZoom, const float minZoom);

    void zoomOut(const float currentZoom, const float maxZoom);

    void moveViewWithMiddleMouseButton();

    void moveViewRelativeToMouseCoords(const sf::Vector2i& oldCoordsOfMouse,
        const sf::Vector2i& newCoordsOfMouse);

private:
    sf::View mCameraView;
    sf::RenderWindow& mWindow;
    SharedContext& mSharedContext;

};


#endif// CAMERASYSTEM_H
