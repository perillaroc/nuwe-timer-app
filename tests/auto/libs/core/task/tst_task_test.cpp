#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QThreadPool>

#include <python_env/python_engine.h>
#include <sms_task/sms_task.h>

using namespace NuweTimer::Core;

class TaskTest : public QObject
{
    Q_OBJECT

public:
    TaskTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testSmsTask();
};

TaskTest::TaskTest()
{
}

void TaskTest::initTestCase()
{
}

void TaskTest::cleanupTestCase()
{
}

// NOTE: this test doesn't work
void TaskTest::testSmsTask()
{
    QSharedPointer<PythonEnv::PythonEngine> python_engine{new PythonEnv::PythonEngine};
    python_engine->setPythonDistributionDir("D:/windroc/project/2017/timer/playground/python/python36-x64");
    python_engine->setPythonExecutableProgramPath("D:/windroc/project/2017/timer/playground/python/python36-x64/python.exe");
    QString python_script_path = "D:/windroc/project/2017/timer/nuwe-timer-app/src/app/nwpc-sms-collector/sms_collector.py";

    QStringList arguments;
    arguments<<"variable";
    arguments<<"--host=xxxxxx";
    arguments<<"--port=22";
    arguments<<"--user=xxxxx";
    arguments<<"--password=xxxx";
    arguments<<"--sms-server=xxxxx";
    arguments<<"--sms-user=xxxxx";
    arguments<<"--sms-password=xxxxxx";
    arguments<<"--node-path=xxxxxxx";

    SmsTask *task = new SmsTask{python_engine, python_script_path, arguments};
    // task->run();
    //
    // QThreadPool::globalInstance()->waitForDone();
}

QTEST_MAIN(TaskTest)

#include "tst_task_test.moc"
