#pragma once

#include "progress_util_global.h"
#include <QObject>
#include <QProcess>
#include <QEventLoop>

namespace ProgressUtil{

struct PROGRESS_UTIL_SHARED_EXPORT SynchronousJobResponse
{
    enum ResponseStatus{
        NormalFinished = 0,
        ErrorFinished,
        FailedToStart
    };

    SynchronousJobResponse();

    void clear();

    ResponseStatus status_;
    QProcess::ExitStatus exit_status_;
    int exit_code_;
    QString std_out_;
    QString std_err_;
};


class PROGRESS_UTIL_SHARED_EXPORT SynchronousJob : public QObject
{
    Q_OBJECT
public:
    explicit SynchronousJob(QObject *parent = 0);

    SynchronousJobResponse run(const QString &program, const QStringList &args);

signals:
//    void signalFinished(int exit_code, QProcess::ExitStatus exit_status);
//    void signalSuccess();

//    void signalStdOutString(const QString &out);
//    void signalStdErrString(const QString &err);

public slots:

private slots:
    void finished(int exit_code, QProcess::ExitStatus exit_status);
    void error(QProcess::ProcessError e);
    void stdOutReady();
    void stdErrReady();

private:
    void clear();


    QProcess process_;
    QEventLoop event_loop_;

    QString program_;

    SynchronousJobResponse response_;
    bool start_failure_flag_;
};

}
