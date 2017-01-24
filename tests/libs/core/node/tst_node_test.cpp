#include <QString>
#include <QtTest>
#include <QCoreApplication>

class NodeTest : public QObject
{
    Q_OBJECT

public:
    NodeTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testCase1_data();
    void testCase1();
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

void NodeTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void NodeTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(NodeTest)

#include "tst_node_test.moc"
