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
    task_->setNode(std::shared_ptr<Node>(this));
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

void Node::begin()
{
    setState(NodeState::State::Queued);
}

void Node::requeue()
{
    setState(NodeState::State::Queued);
}

void Node::run()
{
    if(task_)
    {
        task_->run();
    }
}

bool Node::resolveDependencies()
{
    if(state() == NodeState::State::Completed)
    {
        return false;
    }
    if(trigger_)
    {
        return trigger_->fit();
    }

    return false;
}


