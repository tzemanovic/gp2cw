////////////////////////////////////////////////////
// win32 timer implementation
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "TimerImplWin32.h"

namespace zn
{
    TimerImplWin32::TimerImplWin32()
    {
        m_framesTimeMs = 0;
        m_FPSFrame = 0;
    }
    
    TimerImplWin32::~TimerImplWin32()
    {

    }

    void TimerImplWin32::VStart()
    {
        m_lastTimeMs = GetCurrentTimeMs();
        m_currentTimeMs = CURRENT_TIME_ADDITION;
    }

    const float TimerImplWin32::VUpdate()
    {
        double currentTimeMs = GetCurrentTimeMs();
        double deltaMs = currentTimeMs - m_lastTimeMs;
        m_lastTimeMs = currentTimeMs;
        m_currentTimeMs += deltaMs;

        if( m_FPSFrame++ < FPS_UPDATE )
        {
            m_framesTimeMs += deltaMs;
        }
        else
        {
            m_FPS = static_cast<uint16>( 1000 * FPS_UPDATE / m_framesTimeMs );
            m_framesTimeMs = 0;
            m_FPSFrame = 0;
        }

        return float( deltaMs );
    }

    void TimerImplWin32::VReset()
    {
        m_currentTimeMs = CURRENT_TIME_ADDITION;
    }

    const float TimerImplWin32::VGetTimeMs() const
    {
        return float( m_currentTimeMs - CURRENT_TIME_ADDITION );
    }

    const double TimerImplWin32::GetCurrentTimeMs()
    {
        // use only single thread to calculate time
        HANDLE currentThread = GetCurrentThread();
        DWORD_PTR previousMask = SetThreadAffinityMask( currentThread, 1 );

	    static LARGE_INTEGER frequency;
        LARGE_INTEGER time;
        QueryPerformanceFrequency( &frequency );
        // try using intristic __rdtsc() instead of QPC for better performance
        QueryPerformanceCounter( &time );
        
        // use previously used thread
        SetThreadAffinityMask( currentThread, previousMask );

        return double( 1000 * time.QuadPart / frequency.QuadPart );
    }
    
    const uint16 TimerImplWin32::VGetFPS() const
    {
        return m_FPS;
    }
}