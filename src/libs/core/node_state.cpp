#include "node_state.h"

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
