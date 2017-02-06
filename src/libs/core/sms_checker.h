#pragma once
#include "core_global.h"

#include <QString>

namespace NuweTimer{

namespace Core{

class CORESHARED_EXPORT SmsChecker
{
public:
    SmsChecker();
    virtual ~SmsChecker();

    virtual bool isFit(const QString &test_value);
};

class CORESHARED_EXPORT SmsVariableChecker: public SmsChecker
{
public:
    SmsVariableChecker(const QString &path, const QString &type, const QString &name, const QString &value);
    ~SmsVariableChecker();

    bool isFit(const QString &test_value) override;

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


