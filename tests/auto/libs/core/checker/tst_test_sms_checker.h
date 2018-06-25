#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sms_task/sms_checker.h>

using namespace testing;
using namespace NuweTimer::SmsTaskPackage;

class MockSmsVariableChecker: public SmsVariableChecker
{
public:
    MockSmsVariableChecker(
            const QString &path, const QString &type,
            const QString &name, const QString &value
            ):
        SmsVariableChecker(path,type,name,value)
    {}
    MOCK_CONST_METHOD0(getCurrentDay, QString());
};

TEST(VariableCheckerTest, testFit)
{
    MockSmsVariableChecker mock_var_checker{
        "some_path",
        "date",
        "SMSDATE",
        "current"
    };

    EXPECT_CALL(mock_var_checker, getCurrentDay())
            .WillOnce(Return(QString("20170205")))
            .WillOnce(Return(QString("20170206")))
            .WillOnce(Return(QString("20170207")));

    EXPECT_FALSE(mock_var_checker.isFit("20170206"));
    EXPECT_TRUE(mock_var_checker.isFit("20170206"));
    EXPECT_FALSE(mock_var_checker.isFit("20170206"));
}
