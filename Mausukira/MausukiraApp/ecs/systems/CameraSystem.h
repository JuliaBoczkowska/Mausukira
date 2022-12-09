#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include "SFML/Graphics/Sprite.hpp"
#include "System.h"
#include "Window.h"
#include "ecs/components/TransformComponent.h"

class SharedContext;

class CameraSystem : public System
{
public:
    CameraSystem(entt::registry& registry, SharedContext& sharedContext);

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    void updateCamera();
    void cameraSetView();
    void followPlayer(const TransformComponent& transformComponent);
    void updateBackground();
    void zoomInAndOut(const sf::Event& event);
    void zoomIntoMouseCursor(const sf::Vector2f& oldCoordsOfMouse,
                             const sf::Vector2f& newCoordsOfMouse);
    sf::Vector2f getCursorCoordinates(const sf::Event& event) const;
    void zoomIn(const float currentZoom, const float minZoom);
    void zoomOut(const float currentZoom, const float maxZoom);
    void moveViewWithMiddleMouseButton();

private:
    sf::View mCameraView;
    sf::RenderWindow& mWindow;
    SharedContext& mSharedContext;
    void moveViewRelativeToMouseCoords(const sf::Vector2i& oldCoordsOfMouse,
                                       const sf::Vector2i& newCoordsOfMouse);
};


#endif// CAMERASYSTEM_H
