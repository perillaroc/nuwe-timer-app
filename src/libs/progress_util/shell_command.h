#pragma once

#include "progress_util_global.h"

#include "synchronous_job.h"
#include "async_job.h"

#include <QDateTime>
#include <QFutureWatcher>
#include <QObject>

namespace ProgressUtil{

struct PROGRESS_UTIL_SHARED_EXPORT CommandStep{
    explicit CommandStep(const QString &program, const QStringList &arguments);
    QString program_;
    QStringList arguments_;
};

// TODO: 与 SynchronousJobResponse 的关系

struct PROGRESS_UTIL_SHARED_EXPORT ShellCommandResponse{
    QDateTime request_date_time_;
    int exit_code_;
    QProcess::ExitStatus exit_status_;
    QString std_out_;
    QString std_err_;
};

//Q_DECLARE_METATYPE(ProgressUtil::ShellCommandResponse)

class PROGRESS_UTIL_SHARED_EXPORT ShellCommand : public QObject
{
    Q_OBJECT
public:
    explicit ShellCommand(QObject *parent = 0);
    ~ShellCommand();

    void addCommandStep(const QString& program, const QStringList& argument_list);

    void setRequestTime(const QDateTime &request_date_time);
    QDateTime requestTime() const;
    QFutureWatcher<void> &futureWatcher();

    // 使用异步进程运行
    void execute();

    // 使用同步进程运行
    void run();

    ProgressUtil::SynchronousJobResponse runCommandStep(const CommandStep &step);

signals:
    void signalStdOutString(const QString &out);
    void signalStdErrString(const QString &err);
    void signalFinished(const ShellCommandResponse &shell_command_response);
    void signalSuccess();

protected:
    void asyncRun(QFutureInterface<void> &future_interface);

    QDateTime request_date_time_;

    QList<CommandStep> command_steps_;

    QFutureWatcher<void> watcher_;

    friend class ProgressUtil::AsyncRunJob<ShellCommand>;
};

}


