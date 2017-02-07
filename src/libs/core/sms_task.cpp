#include "sms_task.h"
#include "sms_checker.h"

#include <python_env/python_command.h>
#include <python_env/python_engine.h>

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace PythonEnv;
using namespace ProgressUtil;
using namespace NuweTimer::Core;

SmsTask::SmsTask(QSharedPointer<PythonEnv::PythonEngine> python_engine,
                 const QString &python_script_path,
                 const QStringList &arguments,
                 QObject *parent):
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

void SmsTask::addVariableChecker(std::shared_ptr<SmsVariableChecker> checker)
{
    checker_list_.push_back(checker);
}

void SmsTask::run()
{
    //    qDebug()<<"CheckTask::run check task";
    submit();

    PythonCommand* command = new PythonCommand;

    connect(command, &PythonCommand::signalFinished, this, &SmsTask::slotCommandFinished);

    python_engine_->executePythonScript(
        command,
        python_script_path_,
        arguments_
    );

    init();
}

void SmsTask::slotCommandFinished(const ShellCommandResponse &shell_command_response)
{
    qDebug()<<shell_command_response.std_out_;
    qDebug()<<shell_command_response.std_err_;

    if(shell_command_response.exit_code_ != 0 && shell_command_response.exit_status_ != QProcess::NormalExit)
    {
        abort();
        return;
    }

    QJsonDocument json_document = QJsonDocument::fromJson(shell_command_response.std_out_.toUtf8());
    if(json_document.isEmpty())
    {
        qWarning()<<"[SmsTask::slotCommandFinished] response is not a json docuemnt.";
        abort();
        return;
    }

    QJsonObject root = json_document.object();
    if(root.contains("error"))
    {
        qWarning()<<"[SmsTask::slotCommandFinished] response is error:"<<root["error"].toString();
        abort();
        return;
    }

    QJsonObject node = root["data"].toObject()["response"].toObject()["node"].toObject();

    QJsonArray variable_list = node["variable_list"].toArray();
    QJsonArray generated_variable_list = node["generated_variable_list"].toArray();

    for(auto &checker: checker_list_)
    {
        QString value;
        int index = findVariableInList(variable_list, checker->name());
        if(index != -1)
        {
            value = variable_list[index].toObject()["value"].toString();
        }
        else
        {
            index = findVariableInList(generated_variable_list, checker->name());
            if(index != -1)
            {
               value = generated_variable_list[index].toObject()["value"].toString();
            }
            else
            {
                qWarning()<<"[SmsTask::slotCommandFinished] variable not found.";
                abort();
                return;
            }
        }

        if(!checker->isFit(value))
        {
            abort();
            qWarning()<<"[SmsTask::slotCommandFinished] variable is not fit. Current:"<<value<<"Expect:"<<checker->value();
            return;
        }
    }

    complete();
}

int SmsTask::findVariableInList(const QJsonArray &array, const QString &name) const
{
    int index = -1;
    for(int i=0;i<array.size();i++)
    {
        QJsonObject var = array[i].toObject();
        QString current_name = var["name"].toString();
        if(var["name"].toString() == name)
        {
            index = i;
            break;
        }
    }
    return index;
}
