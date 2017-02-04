#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <core/node.h>
#include <core/task.h>
#include <core/trigger.h>

#include <memory>

using namespace std;
using namespace NuweTimer::Core;

class NodeTest : public QObject
{
    Q_OBJECT

public:
    NodeTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testDefaultNode();
};

NodeTest::NodeTest()
{
}

void NodeTest::initTestCase()
{
}

void NodeTest::cleanupTestCase()
{
}

void NodeTest::testDefaultNode()
{
    unique_ptr<Node> node{new Node};
    QPointer<Task> task{new Task};
    unique_ptr<Trigger> trigger{new Trigger};

    node->setTask(task);    
    node->setTrigger(trigger);

    QCOMPARE(QString::fromStdString(node->name()), QString(""));
    QCOMPARE(node->state(), NodeState::State::Unknown);
    QCOMPARE(node->resolveDepencies(), true);

    node->setName("new name");
    QCOMPARE(QString::fromStdString(node->name()), QString("new name"));
}

QTEST_MAIN(NodeTest)

#include "tst_node_test.moc"
