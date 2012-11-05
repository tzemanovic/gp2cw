#pragma once
////////////////////////////////////////////////////
// timer implementation interface
////////////////////////////////////////////////////

namespace zn
{
    extern const double CURRENT_TIME_ADDITION;
    // update fps every FPS_UPDATE frames
    const uint16 FPS_UPDATE = 10;

    class ITimerImpl
    {
    public:
        ITimerImpl();
        virtual ~ITimerImpl();
        
        virtual void VStart() = 0;
        virtual const float VUpdate() = 0;
        virtual void VReset() = 0;
        virtual const float VGetTimeMs() const = 0;
        virtual const uint16 VGetFPS() const = 0;

    protected:
        double m_lastTimeMs;
        double m_currentTimeMs;
        double m_framesTimeMs;
        uint16 m_FPSFrame;
        uint16 m_FPS;
    };
}