#include "node.h"
#include "trigger.h"
#include "task.h"

using namespace NuweTimer::Core;

Node::Node(const std::string &name)
{
    setName(name);
}

Node::~Node()
{

}

void Node::setName(const std::string &name)
{
    name_ = name;
}

std::string Node::name() const
{
    return name_;
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
    task_->setNode(this);
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
        return true;
    }
}

void Node::run()
{
    if(task_)
    {
        task_->run();
    }
}


