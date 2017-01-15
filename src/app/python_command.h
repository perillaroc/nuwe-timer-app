#pragma once

#include <progress_util/shell_command.h>

namespace PythonEnv{

class PythonCommand : public ProgressUtil::ShellCommand
{
    Q_OBJECT
public:
    explicit PythonCommand(QObject *parent = 0);

signals:


public slots:

private:


};

}
