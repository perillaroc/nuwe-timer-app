#include "sms_task.h"

#include <python_env/python_command.h>
#include <python_env/python_engine.h>

#include <QApplication>
#include <QtDebug>

using namespace PythonEnv;
using namespace NuweTimer::Core;

SmsTask::SmsTask(QSharedPointer<PythonEnv::PythonEngine> python_engine, QObject *parent):
    Task{parent},
    python_engine_{python_engine}
{

}

SmsTask::~SmsTask()
{
//    qDebug()<<"CheckTask delete";
}

void SmsTask::run()
{
//    qDebug()<<"CheckTask::run check task";

    QStringList arguments;
    arguments<<"variable";
    arguments<<"--host=10.20.49.131";
    arguments<<"--port=22";
    arguments<<"--user=nwp";
    arguments<<"--password=nwpop";
    arguments<<"--sms-server=nwpc_op";
    arguments<<"--sms-user=nwp";
    arguments<<"--sms-password=1";
    arguments<<"--node-path=/grapes_meso_v4_1";

    PythonCommand* command = new PythonCommand;

    connect(command, &PythonCommand::signalFinished,
            [=](){
//        qDebug()<<"command finished";
    });

    connect(command, &PythonCommand::signalStdOutString,
            [=](const QString& str){
        qDebug()<<str;
    });

    connect(command, &PythonCommand::signalStdErrString,
            [=](const QString& str){
        qDebug()<<str;
    });

    python_engine_->executePythonScript(
        command,
        QApplication::applicationDirPath()+"\\nwpc-sms-collector\\sms_collector.py",
        arguments
    );

    this->deleteLater();
}
