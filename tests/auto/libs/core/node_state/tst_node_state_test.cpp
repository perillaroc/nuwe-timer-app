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

    void testToString();
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

void NodeStateTest::testToString()
{
    QCOMPARE(QString::fromStdString(NodeState::toString(NodeState::State::Unknown)), QString("unknown"));
    QCOMPARE(QString::fromStdString(NodeState::toString(NodeState::State::Queued)), QString("queued"));
    QCOMPARE(QString::fromStdString(NodeState::toString(NodeState::State::Submitted)), QString("submitted"));
    QCOMPARE(QString::fromStdString(NodeState::toString(NodeState::State::Active)), QString("active"));
    QCOMPARE(QString::fromStdString(NodeState::toString(NodeState::State::Aborted)), QString("aborted"));
    QCOMPARE(QString::fromStdString(NodeState::toString(NodeState::State::Completed)), QString("completed"));
}

QTEST_MAIN(NodeStateTest)

#include "tst_node_state_test.moc"
