#pragma once

#include "core_global.h"
#include "task.h"

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

class CORESHARED_EXPORT SmsTask : public Task
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
    int findVariableInList(const QJsonArray &array, const QString &name) const;

    QSharedPointer<PythonEnv::PythonEngine> python_engine_;

    QString python_script_path_;
    QStringList arguments_;

    std::vector<std::shared_ptr<SmsVariableChecker>> checker_list_;

};

}
}


