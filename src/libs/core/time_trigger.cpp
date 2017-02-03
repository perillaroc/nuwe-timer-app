#include "time_trigger.h"

using namespace NuweTimer::Core;

TimeTrigger::TimeTrigger(const QTime &time):
    Trigger{},
    time_{time}
{

}

std::string TimeTrigger::toString() const
{
    return time_.toString(Qt::TextDate).toStdString();
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
