#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <core/node.h>
#include <core/task.h>
#include <core/trigger.h>

#include <memory>

using namespace std;
using namespace NuweTimer::Core;

Q_DECLARE_METATYPE(NuweTimer::Core::NodeState::State)

class NodeTest : public QObject
{
    Q_OBJECT

public:
    NodeTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testDefaultNode();
    void testSetName();

    void testStateDependencies_data();
    void testStateDependencies();

    void testTiggerDependencies();
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

}

void NodeTest::testSetName()
{
    unique_ptr<Node> node{new Node};
    node->setName("new name");
    QCOMPARE(QString::fromStdString(node->name()), QString("new name"));
}

void NodeTest::testStateDependencies_data()
{
    QTest::addColumn<NodeState::State>("state");
    QTest::addColumn<bool>("is_fit");

    QTest::newRow("unknown") << NodeState::State::Unknown << false;
    QTest::newRow("unknown") << NodeState::State::Queued << true;
    QTest::newRow("unknown") << NodeState::State::Submitted << false;
    QTest::newRow("unknown") << NodeState::State::Active << false;
    QTest::newRow("unknown") << NodeState::State::Aborted << false;
    QTest::newRow("unknown") << NodeState::State::Completed << false;
}

void NodeTest::testStateDependencies()
{
    QFETCH(NodeState::State, state);
    QFETCH(bool, is_fit);

    shared_ptr<Node> node = make_shared<Node>();
    node->setState(state);

    QCOMPARE(node->resolveDependencies(), is_fit);
}

void NodeTest::testTiggerDependencies()
{
    shared_ptr<Node> node = make_shared<Node>();
    QPointer<Task> task{new Task};
    unique_ptr<Trigger> trigger{new Trigger};

    node->setTask(task);
    node->setTrigger(trigger);

    node->setState(NodeState::State::Queued);
    QCOMPARE(node->resolveDependencies(), true);
}

QTEST_MAIN(NodeTest)

#include "tst_node_test.moc"
