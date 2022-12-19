#include "StateHandler.h"
#include "states/GameState.h"
#include "states/MenuState.h"
#include "states/PauseState.h"

StateHandler::StateHandler(SharedContext& sharedCtx)
    : mSharedCtx(sharedCtx)
{
    registerState<MenuState>(StateType::MENU_STATE);
    registerState<GameState>(StateType::GAME_STATE);
    registerState<PauseState>(StateType::PAUSE_STATE, true);

    std::unique_ptr<State> firstState = mStateFactory.find(StateType::MENU_STATE)->second();
    mStates.push_back(std::move(firstState));
}

void StateHandler::switchTo(const StateType& stateType)
{
    mToBeProcessedQueue.emplace_back(std::pair<StateType, ActionType>(stateType, ActionType::PUSH));
}

void StateHandler::removeState(const StateType& stateType)
{
    mToBeProcessedQueue.emplace_back(std::pair<StateType, ActionType>(stateType, ActionType::POP));
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

void StateHandler::handleInput(sf::Event& event)
{
    mStates.back()->handleInput(event);
}

void StateHandler::update(const sf::Time& dt)
{
    closeGameWhenNoStatesLeft();
    mStates.back()->update(dt);
}

void StateHandler::draw()
{
    if (mStates.empty())
    {
        return;
    }
    if (mStates.back()->mIsTransparent && mStates.size() > 1)
    {
        auto itr = mStates.end();
        while (itr != mStates.begin())
        {
            if (itr != mStates.end())
            {
                if (!itr->get()->mIsTransparent)
                {
                    break;
                }
            }
            --itr;
        }
        for (; itr != mStates.end(); ++itr)
        {
            itr->get()->draw();
        }
    }
    else
    {
        mStates.back()->draw();
    }
}

void StateHandler::processQueue()
{
    for (auto elem: mToBeProcessedQueue)
    {
        if (elem.second == ActionType::POP)
        {
            auto itr = mStates.begin();
            while (itr != mStates.end())
            {
                if (itr->get()->mStateType == elem.first)
                {
                    itr = mStates.erase(itr);
                }
                else
                {
                    ++itr;
                }
            }
        }
        if (elem.second == ActionType::PUSH)
        {
            auto state = mStateFactory.find(elem.first)->second();
            mStates.emplace_back(std::move(state));
        }
    }
    mToBeProcessedQueue.clear();
}
