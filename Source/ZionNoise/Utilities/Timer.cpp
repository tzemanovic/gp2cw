////////////////////////////////////////////////////
// timer
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Timer.h"
#include "ITimerImpl.h"

// decide which implementation is required
#ifdef ZN_PLATFORM_WIN32
#   include "Win32\TimerImplWin32.h"
    typedef zn::TimerImplWin32 TimerPlatformImpl;
#endif

namespace zn
{
    Timer::Timer()
    {
        m_pTimerImpl = ZN_NEW TimerPlatformImpl();
    }

    Timer::~Timer()
    {
        ZN_SAFE_DELETE( m_pTimerImpl );
    }

    void Timer::Start()
    {
        m_pTimerImpl->VStart();
    }

    const float Timer::Update()
    {
        return m_pTimerImpl->VUpdate();
    }

    void Timer::Reset()
    {
        m_pTimerImpl->VReset();
    }
    
    const float Timer::GetTimeMs() const
    {
        return m_pTimerImpl->VGetTimeMs();
    }

    const uint16 Timer::GetFPS() const
    {
        return m_pTimerImpl->VGetFPS();
    }
}