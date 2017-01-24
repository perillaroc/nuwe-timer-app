#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QThreadPool>

#include <python_env/python_engine.h>
#include <core/sms_task.h>

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

    SmsTask *task = new SmsTask{python_engine};
    task->run();

    QThreadPool::globalInstance()->waitForDone();
}

QTEST_MAIN(TaskTest)

#include "tst_task_test.moc"
