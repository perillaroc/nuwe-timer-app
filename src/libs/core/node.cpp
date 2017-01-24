#include "node.h"
#include "trigger.h"
#include "task.h"

using namespace NuweTimer::Core;

Node::Node()
{

}

Node::~Node()
{

}

void Node::setTrigger(std::unique_ptr<Trigger> &trigger)
{
    trigger_.reset(trigger.release());
}

Trigger *Node::trigger()
{
    return trigger_.get();
}

void Node::setTask(QPointer<Task> &task)
{
    task_.swap(task);
}

Task *Node::task()
{
    return task_.data();
}

void Node::setState(NodeState::State state)
{
    state_.setState(state);
}

NodeState::State Node::state() const
{
    return state_.state();
}

bool Node::resolveDepencies()
{
    if(trigger_)
    {
        return trigger_->fit();
    }
    else
    {
        return false;
    }
}

void Node::run()
{
    if(task_)
    {
        task_->run();
    }
}


