#pragma once

#include "core_global.h"

namespace NuweTimer{

namespace Core{

class CORESHARED_EXPORT Trigger
{
public:
    Trigger();
    virtual ~Trigger();

    virtual bool fit();

private:

};

}

}
