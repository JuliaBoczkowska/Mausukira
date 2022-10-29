#include "StateHandler.h"
#include "states/IntroState.h"

StateHandler::StateHandler(SharedContext& sharedCtx) : mSharedCtx(sharedCtx)
{
    registerState<IntroState>(StateType::INTRO_STATE);
}

void StateHandler::switchTo(const StateType& stateType)
{
    auto newState = mStateFactory.find(stateType);
    if (newState == mStateFactory.end())
    {
        return;
    }
    states.emplace_back(std::unique_ptr<State>(newState->second()));
}
