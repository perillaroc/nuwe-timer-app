#pragma once

#include <QRunnable>
#include <QSharedPointer>
#include <QPointer>

namespace PythonEnv{
class PythonEngine;
}

class CheckTask : public QObject
{
    Q_OBJECT
public:
    CheckTask(QSharedPointer<PythonEnv::PythonEngine> python_engine, QObject *parent=nullptr);
    ~CheckTask();

    void run();

private:
    QSharedPointer<PythonEnv::PythonEngine> python_engine_;

};

class CheckTaskRunner: public QRunnable
{
public:
    CheckTaskRunner(QPointer<CheckTask> check_task);
    ~CheckTaskRunner();

    void run();
private:
    QPointer<CheckTask> check_task_;
};


