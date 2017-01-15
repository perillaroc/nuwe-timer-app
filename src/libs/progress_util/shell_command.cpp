#include "shell_command.h"

#include <QProcess>
#include <QThreadPool>
#include <QtDebug>

using namespace ProgressUtil;

CommandStep::CommandStep(const QString &program, const QStringList &arguments):
    program_{program},
    arguments_{arguments}
{

}


ShellCommand::ShellCommand(QObject *parent) :
    QObject(parent),
    request_date_time_{QDateTime::currentDateTime()}
{

}

ShellCommand::~ShellCommand()
{
    qDebug()<<"[ShellCommand::~ShellCommand] delete";
}

void ShellCommand::addCommandStep(const QString &program, const QStringList &argument_list)
{
    CommandStep step{program, argument_list};
    command_steps_.append(step);
}

void ShellCommand::setRequestTime(const QDateTime &request_date_time)
{
    request_date_time_ = request_date_time;
}

QDateTime ShellCommand::requestTime() const
{
    return request_date_time_;
}

QFutureWatcher<void> &ShellCommand::futureWatcher()
{
    return watcher_;
}

void ShellCommand::execute()
{
    if(command_steps_.isEmpty())
        return;
    QFuture<void> future = runAsyncJob(&ShellCommand::asyncRun, this);
    watcher_.setFuture(future);
}

void ShellCommand::run()
{
    int command_step_size = command_steps_.length();
    for(int i=0;i<command_step_size;i++)
    {
        CommandStep command_step = command_steps_.at(i);
        runCommandStep(command_step);
    }

    this->deleteLater();
}

SynchronousJobResponse ShellCommand::runCommandStep(const CommandStep &step)
{
    SynchronousJobResponse response;

    SynchronousJob job;

    response = job.run(step.program_, step.arguments_);

    qDebug()<<"[ShellCommand::runCommandStep] SynchronousJob success";

    emit signalStdOutString(response.std_out_);
    if(!response.std_err_.isEmpty())
    {
        emit signalStdErrString(response.std_err_);
    }

    ShellCommandResponse shell_command_response;
    shell_command_response.exit_code_ = response.exit_code_;
    shell_command_response.exit_status_ = response.exit_status_;
    shell_command_response.std_out_ = response.std_out_;
    shell_command_response.std_err_ = response.std_err_;
    shell_command_response.request_date_time_ = this->request_date_time_;

    emit signalFinished(shell_command_response);

    if(response.exit_code_ == 0 && response.exit_status_ == QProcess::NormalExit)
    {
        emit signalSuccess();
    }
    else
    {
        qDebug()<<"[ShellCommand::runCommandStep] SynchronousJob failed";
    }

    return response;
}

void ShellCommand::asyncRun(QFutureInterface<void> &future_interface)
{
    future_interface.setProgressValue(10);
    int command_step_size = command_steps_.length();
    for(int i=0;i<command_step_size;i++)
    {
        CommandStep command_step = command_steps_.at(i);
        runCommandStep(command_step);
        future_interface.setProgressValue( (i+1)/command_step_size * 80 + 10);
    }
    this->deleteLater();
    future_interface.setProgressValue(100);
}


