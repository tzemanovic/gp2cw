#pragma once
////////////////////////////////////////////////////
// timer
////////////////////////////////////////////////////

namespace zn
{
    class ITimerImpl;
    class Timer
    {
    public:
        Timer();
        ~Timer();

        // start the timer
        void Start();
        // update the timer - returns delta time
        const float Update();
        // reset the timer
        void Reset();
        // get elapsed time in ms
        const float GetTimeMs() const;
        // get FPS
        const uint16 GetFPS() const;
    private:
        ITimerImpl* m_pTimerImpl;
    };
}