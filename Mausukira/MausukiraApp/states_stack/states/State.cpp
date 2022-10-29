#include "State.h"
#include "../StateHandler.h"

State::State(std::unique_ptr<StateHandler> stateHandler, StateType type)
    :
    mStateHandler(std::move(stateHandler)),
    mStateType(type)
{

}