#pragma once

#include "sms_task_global.h"

#include <core/task.h>
#include <progress_util/shell_command.h>

#include <QSharedPointer>
#include <QJsonArray>

#include <vector>
#include <memory>

namespace PythonEnv{
class PythonEngine;
}

namespace NuweTimer{

namespace Core{

class SmsVariableChecker;

class SmsTask : public Task
{
    Q_OBJECT
public:
    SmsTask(
            QSharedPointer<PythonEnv::PythonEngine> python_engine,
            const QString &python_script_path,
            const QStringList &arguments,
            QObject *parent=nullptr
            );
    ~SmsTask();

    void addVariableChecker(std::shared_ptr<SmsVariableChecker> checker);

    void run() override;

private slots:
    void slotCommandFinished(const ProgressUtil::ShellCommandResponse &shell_command_response);

private:
    QString findVariable(const QString &name, const QJsonArray &var_array, const QJsonArray &genvar_array, bool &ok) const;
    QString findVariableInArray(const QString &name, const QJsonArray &array, bool &ok) const;

    QSharedPointer<PythonEnv::PythonEngine> python_engine_;

    QString python_script_path_;
    QStringList arguments_;

    std::vector<std::shared_ptr<SmsVariableChecker>> checker_list_;

};

}
}


