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
        
        // start the timer
        virtual void VStart() = 0;
        // update the timer - returns delta time
        virtual const float VUpdate() = 0;
        // reset the timer
        virtual void VReset() = 0;
        // get elapsed time in ms
        virtual const float VGetTimeMs() const = 0;

        // accessors
        const uint16 VGetFPS() const { return m_FPS; }

    protected:
        // time of last update
        double m_lastTimeMs;
        // current time
        double m_currentTimeMs;
        // used for collecting elapsed time for FPS calculations
        double m_framesTimeMs;
        // frame number
        uint16 m_FPSFrame;
        // fps
        uint16 m_FPS;
    };
}