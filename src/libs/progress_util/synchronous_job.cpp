#include "synchronous_job.h"

#include <QApplication>
#include <QThread>
#include <QtDebug>

using namespace ProgressUtil;

namespace ProgressUtil{
static bool isGuiThread(){
    return QThread::currentThread() == QCoreApplication::instance()->thread();
}
}

SynchronousJobResponse::SynchronousJobResponse():
    exit_code_{-1},
    status_{FailedToStart},
    exit_status_{QProcess::CrashExit}
{

}

void SynchronousJobResponse::clear()
{
    status_ = FailedToStart;
    exit_status_ = QProcess::CrashExit;
    exit_code_ = -1;
    std_out_.clear();
    std_err_.clear();
}


SynchronousJob::SynchronousJob(QObject *parent) : QObject(parent),
    start_failure_flag_{false}
{
    connect(&process_,
            static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this, &SynchronousJob::finished);
    connect(&process_, &QProcess::errorOccurred,
            this, &SynchronousJob::error);
    connect(&process_, &QProcess::readyReadStandardOutput,
            this, &SynchronousJob::stdOutReady);
    connect(&process_, &QProcess::readyReadStandardError,
            this, &SynchronousJob::stdErrReady);
}

SynchronousJobResponse SynchronousJob::run(const QString &program, const QStringList &args)
{
    clear();
    program_ = program;

    process_.start(program, args, QIODevice::ReadOnly);
    process_.closeWriteChannel();

    if(!start_failure_flag_)
    {
        if(isGuiThread())
            QApplication::setOverrideCursor(Qt::WaitCursor);
        event_loop_.exec(QEventLoop::ExcludeUserInputEvents);

        response_.std_out_ = process_.readAllStandardOutput();
        response_.std_err_ = process_.readAllStandardError();

//        emit signalStdOutString(response_.std_out_);
//        if(!response_.std_err_.isEmpty())
//        {
//            emit signalStdErrString(response_.std_err_);
//        }

//        if(response_.exit_code_ == 0)
//        {
//            emit signalSuccess();
//        }

        if(isGuiThread())
            QApplication::restoreOverrideCursor();
    }
    return response_;
}

void SynchronousJob::finished(int exit_code, QProcess::ExitStatus exit_status)
{
    qDebug()<<"[SynchronousJob::finished] exit status:"<<exit_status;
    switch(exit_status)
    {
    case QProcess::NormalExit:
        response_.exit_code_ = exit_code;
        response_.status_ = SynchronousJobResponse::NormalFinished;
        break;
    case QProcess::CrashExit:
        response_.exit_code_ = -1;
        response_.status_ = SynchronousJobResponse::ErrorFinished;
        break;
    }
    response_.exit_status_ = exit_status;
    event_loop_.quit();
//    emit signalFinished(exit_code, exit_status);
}

void SynchronousJob::error(QProcess::ProcessError e)
{
    qDebug()<<"[SynchronousJob::error] error:"<<e;
    switch(e){
    case QProcess::FailedToStart:
        response_.status_ = SynchronousJobResponse::FailedToStart;
        break;
    case QProcess::Crashed:
        response_.status_ = SynchronousJobResponse::ErrorFinished;
        break;
    default:
        response_.status_ = SynchronousJobResponse::ErrorFinished;
        break;
    }
    start_failure_flag_ = true;
    event_loop_.quit();
}

void SynchronousJob::stdOutReady()
{

}

void SynchronousJob::stdErrReady()
{

}

void SynchronousJob::clear()
{
    response_.clear();
    start_failure_flag_ = false;
}

