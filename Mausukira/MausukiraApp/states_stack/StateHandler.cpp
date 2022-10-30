#include "StateHandler.h"
#include "states/GameState.h"
#include "states/IntroState.h"
#include "states/MenuState.h"

StateHandler::StateHandler(SharedContext& sharedCtx)
    : mSharedCtx(sharedCtx)
{
    registerState<IntroState>(StateType::INTRO_STATE);
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
    mStates.emplace_back(std::unique_ptr<State>(newState->second()));
}
void StateHandler::closeGameWhenNoStatesLeft()
{
    if (mStates.empty())
    {
        mSharedCtx.window().close();
    }
}
