#pragma once

#include "trigger.h"
#include "core_global.h"
#include <QTime>

namespace NuweTimer{

namespace Core{

class CORESHARED_EXPORT TimeTrigger : public Trigger
{
public:
    TimeTrigger(const QTime &time);

    bool fit();

protected:
    // this is virtual function because of using Google C++ Mocking Framework.
    // future work is need to create mock for non-virtual method.
    virtual QTime getCurrentTime() const;

    QTime time_;
};

}
}
