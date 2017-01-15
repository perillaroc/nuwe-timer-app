#include "check_task.h"

#include <QtDebug>

CheckTask::CheckTask()
{

}

CheckTask::~CheckTask()
{
    qDebug()<<"CheckTask delete";
}

void CheckTask::run()
{
    qDebug()<<"CheckTask::run check task";
}
