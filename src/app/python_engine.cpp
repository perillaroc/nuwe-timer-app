#include "python_engine.h"
#include "python_command.h"

#include <QMetaType>
#include <QtDebug>

using namespace PythonEnv;

PythonEngine::PythonEngine(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<ProgressUtil::ShellCommandResponse>("ShellCommandResponse");
}

PythonEngine::~PythonEngine()
{

}

QString PythonEngine::pythonDistributionDir() const
{
    return python_distribution_dir_;
}

void PythonEngine::setPythonDistributionDir(const QString &python_distribution_dir)
{
    python_distribution_dir_ = python_distribution_dir;
}

QString PythonEngine::pythonExecutableProgramPath() const
{
    return python_executable_program_path_;
}

void PythonEngine::setPythonExecutableProgramPath(const QString &python_executable_program_path)
{
    python_executable_program_path_ = python_executable_program_path;
}

PythonCommand *PythonEngine::createPythonCommand()
{
    PythonCommand *command = new PythonCommand{this};

    //    connect(command, &PythonCommand::signalStdErrString,
    //            [=](const QString &out)
    //            {
    //                qDebug()<<"[PythonEngine::executePythonScript] stderr:"<<out;
    //            }

    //    );
    //    connect(command, &PythonCommand::signalStdOutString,
    //            [=](const QString &out)
    //            {
    //                qDebug()<<"[PythonEngine::executePythonScript] stdout:"<<out;
    //            }

    //    );

    //    connect(command, &PythonCommand::signalFinished,
    //            [=](int exit_code, QProcess::ExitStatus exit_status)
    //            {
    //                qDebug()<<"[PythonEngine::executePythonScript] exit_code:"<<exit_code;
    //                qDebug()<<"[PythonEngine::executePythonScript] exit_status:"<<exit_status;
    //            }
    //    );

    return command;
}

QFuture<void> PythonEngine::executePythonScript(PythonCommand *command, const QString &script_path, const QStringList &argument_list)
{
    qDebug()<<"[PythonEngine::executePythonScript] start";

    QStringList process_arg_list;
    process_arg_list<<script_path;
    foreach(QString str, argument_list)
        process_arg_list<<str;

    command->addCommandStep(python_executable_program_path_, process_arg_list);
    //command->run();
    command->execute();

    qDebug()<<"[PythonEngine::executePythonScript] end";
    return command->futureWatcher().future();
}

void PythonEngine::runPythonScript(PythonCommand *command, const QString &script_path, const QStringList &argument_list)
{
    qDebug()<<"[PythonEngine::runPythonScript] start";

    QStringList process_arg_list;
    process_arg_list<<script_path;
    foreach(QString str, argument_list)
        process_arg_list<<str;

    command->addCommandStep(python_executable_program_path_, process_arg_list);
    command->run();
//    command->execute();

    qDebug()<<"[PythonEngine::runPythonScript] end";
    return;
}
