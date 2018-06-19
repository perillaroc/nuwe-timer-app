#pragma once
#include "sms_task_global.h"

#include <QString>

namespace NuweTimer{

namespace Core{

class SmsVariableChecker
{
public:
    SmsVariableChecker(const QString &path, const QString &type, const QString &name, const QString &value);
    ~SmsVariableChecker();

    QString path() const { return path_; }
    QString type() const { return type_; }
    QString name() const { return name_; }
    QString value() const { return value_; }

    bool isFit(const QString &test_value);

protected:
    // same as TimeTrigger class in time_trigger.
    // virutal for using google c++ test. need future work.
    virtual QString getCurrentDay() const;

private:
    QString path_;
    QString type_;
    QString name_;
    QString value_;
};

}
}


