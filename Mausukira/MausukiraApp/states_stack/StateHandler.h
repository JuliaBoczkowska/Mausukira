#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include "SharedContext.h"
#include "states/State.h"
#include <functional>
#include <unordered_map>

class StateHandler
{
    enum class ActionType
    {
        POP,
        PUSH,
    };

public:
    using StateFactory = std::unordered_map<StateType, std::function<std::unique_ptr<State>(void)>>;
    using States = std::vector<std::unique_ptr<State>>;

    StateHandler(SharedContext& sharedCtx);
    ~StateHandler() = default;

    void handleInput(sf::Event& event);
    void update(const sf::Time& dt);
    void draw();

    void processQueue();
    void switchTo(const StateType& stateType);
    void removeState(const StateType& stateType);
    SharedContext& context();

    template<class State, typename... Args>
    void registerState(const StateType& type, Args&&... args)
    {
        mStateFactory[type] = [args..., this, type]() -> std::unique_ptr<State>
        {
            return std::make_unique<State>((*this), type, mSharedCtx.window().getDefaultView(),
                                           args...);
        };
    }

private:
    void closeGameWhenNoStatesLeft();

private:
    StateFactory mStateFactory;
    States mStates;
    std::vector<std::pair<StateType, ActionType>> mToBeProcessedQueue;
    SharedContext& mSharedCtx;
};


#endif// STATEHANDLER_H
