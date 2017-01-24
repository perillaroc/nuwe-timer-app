#include "time_trigger.h"

using namespace NuweTimer::Core;

TimeTrigger::TimeTrigger(const QTime &time):
    Trigger{},
    time_{time}
{

}

bool TimeTrigger::fit()
{
    QTime current_time = getCurrentTime();
    return current_time >= time_;
}

QTime TimeTrigger::getCurrentTime() const
{
    return QTime::currentTime();
}
