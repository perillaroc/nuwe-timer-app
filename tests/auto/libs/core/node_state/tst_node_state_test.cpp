#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <core/node_state.h>

using namespace NuweTimer::Core;

class NodeStateTest : public QObject
{
    Q_OBJECT

public:
    NodeStateTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNodeState();
};

NodeStateTest::NodeStateTest()
{
}

void NodeStateTest::initTestCase()
{
}

void NodeStateTest::cleanupTestCase()
{
}

void NodeStateTest::testNodeState()
{
    NodeState state;
    QCOMPARE(state.state(), NodeState::State::Unknown);

    state.setState(NodeState::State::Queued);
    QCOMPARE(state.state(), NodeState::State::Queued);
}

QTEST_MAIN(NodeStateTest)

#include "tst_node_state_test.moc"
