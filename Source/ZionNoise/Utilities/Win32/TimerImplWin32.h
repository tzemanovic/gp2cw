#pragma once
////////////////////////////////////////////////////
// win32 timer implementation
////////////////////////////////////////////////////

#include "..\ITimerImpl.h"

namespace zn
{
    class TimerImplWin32 : public ITimerImpl
    {
    public:
        TimerImplWin32();
        ~TimerImplWin32();
        
        // start the timer
        void VStart();
        // update the timer - returns delta time
        const float VUpdate();
        // reset the timer
        void VReset();
        // get elapsed time in ms
        const float VGetTimeMs() const;

    private:
        // calculate current time
        const double GetCurrentTimeMs();
    };
}