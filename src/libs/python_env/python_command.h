#pragma once
#include "python_env_global.h"
#include <progress_util/shell_command.h>

namespace PythonEnv{

class PYTHON_ENV_SHARED_EXPORT PythonCommand : public ProgressUtil::ShellCommand
{
    Q_OBJECT
public:
    explicit PythonCommand(QObject *parent = 0);

signals:


public slots:

private:


};

}
