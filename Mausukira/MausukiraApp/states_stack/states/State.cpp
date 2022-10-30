#include "State.h"
#include "../StateHandler.h"

State::State(StateHandler& stateHandler, StateType type)
    : mStateHandler(stateHandler)
    , mStateType(type)
{
}