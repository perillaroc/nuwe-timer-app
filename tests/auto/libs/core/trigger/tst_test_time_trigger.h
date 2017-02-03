#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <core/time_trigger.h>

using namespace testing;
using namespace NuweTimer::Core;

class MockTimeTrigger: public TimeTrigger
{
public:
    MockTimeTrigger(const QTime &time):
        TimeTrigger(time)
    {}
    MOCK_CONST_METHOD0(getCurrentTime, QTime());
};

TEST(TimeTriggerTest, testToString)
{
    TimeTrigger time_trigger(QTime(12,0,0));
    EXPECT_EQ(time_trigger.toString(), "12:00:00");
}

TEST(TimeTriggerTest, testFit)
{
    MockTimeTrigger mock_time_trigger(QTime(12,0,0));
    EXPECT_CALL(mock_time_trigger, getCurrentTime())
            .WillOnce(Return(QTime(11,0,0)))
            .WillOnce(Return(QTime(12,0,0)))
            .WillOnce(Return(QTime(13,0,0)));
    EXPECT_FALSE(mock_time_trigger.fit());
    EXPECT_TRUE(mock_time_trigger.fit());
    EXPECT_TRUE(mock_time_trigger.fit());
}

TEST(TriggerTest, testTrigger)
{
    Trigger trigger;
    EXPECT_TRUE(trigger.fit());
    EXPECT_EQ(trigger.toString(), "");
}
