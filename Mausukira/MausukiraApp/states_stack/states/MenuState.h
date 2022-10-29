#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "State.h"
#include "../StateHandler.h"
#include "../../gui/GuiComponents.h"

class StateHandler;

class MenuState : public State
{
public:
    MenuState(std::unique_ptr<StateHandler> stateManager, StateType type);
    ~MenuState() = default;

    void handleInput(sf::Event &event) override;
    void update(const sf::Time& dt) override;
    void draw() override;

private:
    GuiComponents mGuiComponents;
};


#endif //MENUSTATE_H