#pragma once

#include "core_global.h"
#include "task.h"

#include <progress_util/shell_command.h>

#include <QSharedPointer>

#include <vector>
#include <memory>

namespace PythonEnv{
class PythonEngine;
}

namespace NuweTimer{

namespace Core{

class SmsChecker;

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

    void addChecker(std::shared_ptr<SmsChecker> checker);

    void run() override;

private slots:
    void slotCommandFinished(const ProgressUtil::ShellCommandResponse &shell_command_response);

private:
    QSharedPointer<PythonEnv::PythonEngine> python_engine_;

    QString python_script_path_;
    QStringList arguments_;

    std::vector<std::shared_ptr<SmsChecker>> checker_list_;

};

}
}


