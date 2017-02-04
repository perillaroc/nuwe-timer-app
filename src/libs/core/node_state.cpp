#include "node_state.h"

#include <exception>

using namespace NuweTimer::Core;

NodeState::NodeState(State s):
    state_{s}
{
}

NodeState::State NodeState::state() const
{
    return state_;
}

void NodeState::setState(NodeState::State state)
{
    state_ = state;
}

std::string NodeState::toString(const State &state)
{
    switch(state)
    {
    case State::Unknown:
        return "unknown";
    case State::Queued:
        return "queued";
    case State::Submitted:
        return "submitted";
    case State::Active:
        return "active";
    case State::Aborted:
        return "aborted";
    case State::Completed:
        return "completed";
    }

    throw std::exception("unsupported state.");
}
