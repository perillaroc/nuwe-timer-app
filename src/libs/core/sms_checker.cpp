#include "sms_checker.h"

#include <QDate>
#include <QtDebug>

using namespace NuweTimer::Core;


SmsVariableChecker::SmsVariableChecker(
        const QString &path, const QString &type,
        const QString &name, const QString &value ):
    path_{path},
    type_{type},
    name_{name},
    value_{value}
{

}

SmsVariableChecker::~SmsVariableChecker()
{

}

bool SmsVariableChecker::isFit(const QString &test_value)
{
    if(type_ == "date")
    {
        if(value_ == "current")
        {
            QString current_day_string = getCurrentDay();
            return current_day_string == test_value;
        }
    }
    qCritical()<<"[SmsVariableChecker::isFit] type and value are not supported now.";
    return false;
}

QString SmsVariableChecker::getCurrentDay() const
{
    QDate current_day = QDate::currentDate();
    QString current_day_string = current_day.toString("yyyyMMdd");
    return current_day_string;
}
