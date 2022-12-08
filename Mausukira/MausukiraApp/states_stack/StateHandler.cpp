#include "StateHandler.h"
#include "states/GameState.h"
#include "states/MenuState.h"

StateHandler::StateHandler(SharedContext& sharedCtx)
    : mSharedCtx(sharedCtx)
{
    registerState<MenuState>(StateType::MENU_STATE);
    registerState<GameState>(StateType::GAME_STATE);

    std::unique_ptr<State> firstState = mStateFactory.find(StateType::GAME_STATE)->second();
    mStates.push_back(std::move(firstState));
}

void StateHandler::switchTo(const StateType& stateType)
{
    auto newState = mStateFactory.find(stateType);
    if (newState == mStateFactory.end())
    {
        return;
    }

    auto state = std::unique_ptr<State>(newState->second());
    mSharedCtx.window().setView(state->GetView());

    mStates.emplace_back(std::move(state));
}

void StateHandler::closeGameWhenNoStatesLeft()
{
    if (mStates.empty())
    {
        mSharedCtx.window().close();
    }
}
SharedContext& StateHandler::context()
{
    return mSharedCtx;
}
StateHandler::States& StateHandler::states()
{
    return mStates;
}

State& StateHandler::currentState()
{
    return *states().begin()->get();
}
