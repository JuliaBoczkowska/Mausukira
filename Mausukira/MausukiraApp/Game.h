#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
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
     * @brief Main loop of the game. Here, all the elementary actions line update, handle events or render takes place
     */
    void run();

private:
    /**
     * @brief Updates logic of the game (moving sprites, collision detection etc.).
     */
    void update();

    /**
     * @brief Render every drawable object to the window.
     */
    void render();
    void MoveSprite(std::unique_ptr<EventDetails> details);


private:
    const sf::Time deltaTime = sf::seconds(1.f / 60.f);
    Window mWindow;
    StateHandler mStateHandler;
    SharedContext mContext{mWindow};
    sf::RectangleShape rect;
};
#endif //GAME_H
