#pragma once
#include "core_global.h"

namespace NuweTimer{

namespace Core{

class CORESHARED_EXPORT NodeState
{
public:
    enum class State{
        Unknown,
        Queued,
        Submitted,
        Active,
        Aborted,
        Completed
    };

    NodeState(State s = State::Unknown);

    State state() const;
    void setState(State state);

private:
    State state_;
};

}
}
