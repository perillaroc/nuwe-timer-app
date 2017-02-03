#pragma once

#include "core_global.h"
#include <QObject>

namespace NuweTimer{

namespace Core{

class CORESHARED_EXPORT Task: public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = nullptr);
    virtual ~Task();

    virtual void run() = 0;

private:

};

}
}
