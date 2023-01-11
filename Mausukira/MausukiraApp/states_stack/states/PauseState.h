#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"

class PauseState : public State
{
public:
    PauseState(StateHandler& stateManager, StateType type, sf::View view, bool isTransparent);

    ~PauseState() = default;

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw() override;

private:
    void setupText();
    void setupBackground();

private:
    sf::Font font;
    sf::Text mPaused;
    sf::Text mText;
    sf::RectangleShape background;
};

#endif// PAUSESTATE_H
