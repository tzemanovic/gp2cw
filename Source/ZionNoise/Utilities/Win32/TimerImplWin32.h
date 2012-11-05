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

        void VStart();
        const float VUpdate();
        void VReset();
        const float VGetTimeMs() const;
        const uint16 VGetFPS() const;

    private:
        const double GetCurrentTimeMs();
    };
}