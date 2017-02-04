#pragma once

#include "core_global.h"
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

    void setNode(Node *node);

    virtual void run();

    virtual void submit();
    virtual void init();
    virtual void abort();
    virtual void complete();

private:
    Node *node_;
};

}
}
