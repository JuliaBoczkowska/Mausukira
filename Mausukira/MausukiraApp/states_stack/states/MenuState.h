#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "TGUI/Backends/SFML/GuiSFML.hpp"
#include "TGUI/Widgets/Button.hpp"

class MenuState : public State
{
public:
    MenuState(StateHandler& stateManager, StateType type, sf::View view);

    ~MenuState() = default;

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw() override;

private:
    void setupBackground();
    void setupStartButton();
    void setupQuitButton();
    void setupText();

private:
    tgui::Theme theme;
    tgui::GuiSFML gui;
    sf::Font font;
    sf::Text mGameTitle;
};

#endif// MENUSTATE_H