#pragma once

#include "core_global.h"
#include "node_state.h"

#include <string>
#include <memory>
#include <QPointer>

namespace NuweTimer{

namespace Core{

class Trigger;
class Task;

class CORESHARED_EXPORT Node
{
public:
    Node(const std::string &name = "");
    virtual ~Node();

    void setName(const std::string &name);
    std::string name() const;

    void setTrigger(std::unique_ptr<Trigger> &trigger);
    Trigger *trigger();

    void setTask(QPointer<Task> &task);
    Task *task();

    void setState(NodeState::State state);
    NodeState::State state() const;

    virtual bool resolveDepencies();

    void run();

protected:
    std::string name_;
    NodeState state_;
    std::unique_ptr<Trigger> trigger_;
    QPointer<Task> task_;
};

}

}
