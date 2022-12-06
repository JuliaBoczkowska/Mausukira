#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"
#include "Window.h"
#include "states_stack/StateHandler.h"

class EventDetails;

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
    ~Game() = default;

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
    void update(const sf::Time& dt);

    /**
     * @brief Render every drawable object to the window.
     */
    void render();

    //    void MoveSprite(std::unique_ptr<EventDetails> details);


private:
    const sf::Time deltaTime = sf::seconds(1.f / 60.f);
    Window mWindow;
    TextureManager mTextureManager;
    SharedContext mContext;
    StateHandler mStateHandler;
};

#endif// GAME_H
