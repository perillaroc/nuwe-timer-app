#include "task.h"
#include "node.h"

using namespace NuweTimer::Core;

Task::Task(QObject *parent):
    QObject{parent},
    node_{nullptr}
{
}

Task::~Task()
{

}

void Task::setNode(Node *node)
{
    node_ = node;
}

void Task::run()
{

}

void Task::submit()
{
    if(node_){
        node_->setState(NodeState::State::Submitted);
    }
}

void Task::init()
{
    if(node_){
        node_->setState(NodeState::State::Active);
    }
}

void Task::abort()
{
    if(node_){
        node_->setState(NodeState::State::Aborted);
    }
}

void Task::complete()
{
    if(node_){
        node_->setState(NodeState::State::Completed);
    }
}
