#include "sms_task.h"

#include <python_env/python_command.h>
#include <python_env/python_engine.h>

#include <QApplication>
#include <QtDebug>

using namespace PythonEnv;
using namespace NuweTimer::Core;

SmsTask::SmsTask(QSharedPointer<PythonEnv::PythonEngine> python_engine, const QString &python_script_path, const QStringList &arguments, QObject *parent):
    Task{parent},
    python_engine_{python_engine},
    python_script_path_{python_script_path},
    arguments_{arguments}
{
}

SmsTask::~SmsTask()
{
    //    qDebug()<<"CheckTask delete";
}

void SmsTask::run()
{
    //    qDebug()<<"CheckTask::run check task";

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
        python_script_path_,
        arguments_
    );

    this->deleteLater();
}
