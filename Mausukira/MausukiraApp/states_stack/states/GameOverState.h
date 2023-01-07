#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "TGUI/Backends/SFML/GuiSFML.hpp"
#include "TGUI/Widgets/Button.hpp"

class GameOverState : public State
{
public:
    GameOverState(StateHandler& stateManager, StateType type, sf::View view, bool isTransparent);

    ~GameOverState() = default;

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw() override;

private:
    void setupPlayAgainButton();
    void setupQuitButton();
    void setupMainMenuButton();
    void setupText();

private:
    tgui::GuiSFML gui;
    sf::Font font;
    sf::Text mTitle;
    sf::Text mText;
    sf::RectangleShape background;
};

#endif// GAMEOVERSTATE_H
