#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../../gui/GuiComponents.h"
#include "State.h"

class MenuState : public State
{
public:
    MenuState(StateHandler& stateManager, StateType type);
    ~MenuState() = default;

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw() override;

private:
    GuiComponents mGuiComponents;
};

#endif//MENUSTATE_H