#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "State.h"

class IntroState : public State
{
public:
    IntroState(StateHandler& stateManager, StateType type);
    ~IntroState() = default;

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw() override;
};

#endif//INTROSTATE_H
