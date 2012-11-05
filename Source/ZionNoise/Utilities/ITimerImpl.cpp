////////////////////////////////////////////////////
// timer implementation interface
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "ITimerImpl.h"

namespace zn
{
    // http://randomascii.wordpress.com/2012/02/13/dont-store-that-in-a-float/
    // start timer at 2^32 to gain best precision
    const double CURRENT_TIME_ADDITION = 4294967296;

    ITimerImpl::ITimerImpl()
    {
    
    }

    ITimerImpl::~ITimerImpl()
    {

    }
}