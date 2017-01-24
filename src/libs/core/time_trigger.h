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
    virtual QTime getCurrentTime() const;

    QTime time_;
};

}
}
