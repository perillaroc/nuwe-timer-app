#pragma once
#include "core_global.h"
#include <string>

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

    static std::string toString(const State &state);

private:
    State state_;
};

}
}
