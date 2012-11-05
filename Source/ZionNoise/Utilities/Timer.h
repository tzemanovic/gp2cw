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

        void Start();
        const float Update();
        void Reset();

        const float GetTimeMs() const;
        const uint16 GetFPS() const;
    private:
        ITimerImpl* m_pTimerImpl;
    };
}