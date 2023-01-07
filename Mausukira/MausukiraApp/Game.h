#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"
#include <memory>

namespace sf
{
class Event;
}

class Window;
class TextureManager;
class SharedContext;
class StateHandler;

class Game
{
public:
    /**
     * @brief Constructor of the Game class.
     */
    Game();

    /**
     * @brief Destructor of the Game class
     */
    ~Game();

    /**
     * @brief Main loop of the game. Here, all the elementary actions line moveBy, handle events or
     * render takes place
     */
    void run();

private:
    /**
     * @brief Updates logic of the game (moving sprites, collision detection etc.).
     * @param dt Delta time.
     */
    void update(const sf::Time& dt, std::unique_ptr<StateHandler>& mStateHandler);

    /**
     * @brief Render every drawable object to the window.
     */
    void render(std::unique_ptr<StateHandler>& mStateHandler);

    void handlePolledEvents(sf::Event& event, std::unique_ptr<StateHandler>& mStateHandler);

    void lateUpdate(std::unique_ptr<StateHandler>& mStateHandler);

private:
    const sf::Time deltaTime = sf::seconds(1.f / 60.f);
    std::unique_ptr<Window> mWindow;
    std::unique_ptr<TextureManager> mTextureManager;
    std::unique_ptr<SharedContext> mContext;
};

#endif// GAME_H
