#pragma once
////////////////////////////////////////////////////
// interface to be inherited by non copyable class
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"

class INoCopy
{
protected:
    INoCopy() {}
    ~INoCopy() {}
private:
    INoCopy( const INoCopy& );
    const INoCopy& operator=( const INoCopy& );
};