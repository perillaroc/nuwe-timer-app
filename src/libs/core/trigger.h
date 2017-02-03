#pragma once

#include "core_global.h"
#include <string>

namespace NuweTimer{

namespace Core{

class CORESHARED_EXPORT Trigger
{
public:
    Trigger();
    virtual ~Trigger();

    virtual std::string toString() const;
    virtual bool fit();

private:

};

}

}
