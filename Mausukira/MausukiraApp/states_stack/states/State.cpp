#include "State.h"
#include "../StateHandler.h"

State::State(StateHandler& stateHandler, StateType type, sf::View view)
    : mStateHandler(stateHandler)
    , mStateType(type)
    , mView(view)
{
}