#pragma once

#include "core_global.h"
#include <memory>
#include <QObject>

namespace NuweTimer{

namespace Core{

class Node;

class CORESHARED_EXPORT Task: public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = nullptr);
    virtual ~Task();

    void setNode(const std::shared_ptr<Node> &node);

    virtual void run();

    virtual void submit();
    virtual void init();
    virtual void abort();
    virtual void complete();

private:
    std::shared_ptr<Node> node_;
};

}
}
