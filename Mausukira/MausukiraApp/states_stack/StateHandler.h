#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include "SharedContext.h"
#include "states/State.h"
#include <functional>
#include <unordered_map>

class StateHandler
{
public:
    using StateFactory = std::unordered_map<StateType, std::function<std::unique_ptr<State>(void)>>;
    using States = std::vector<std::unique_ptr<State>>;

    StateHandler(SharedContext& sharedCtx);

    ~StateHandler() = default;

    void switchTo(const StateType& stateType);

    void closeGameWhenNoStatesLeft();

    SharedContext& context()
    {
        return mSharedCtx;
    }

    States& states()
    {
        return mStates;
    }

    template<class State>
    void registerState(const StateType& type)
    {
        mStateFactory[type] = [this, type]() -> std::unique_ptr<State>
        {
            return std::make_unique<State>((*this), type,
                                           mSharedCtx.window->mRenderWindow.getDefaultView());
        };
    }

private:
    StateFactory mStateFactory;
    States mStates;
    SharedContext& mSharedCtx;
};


#endif// STATEHANDLER_H
