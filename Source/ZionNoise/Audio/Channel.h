#pragma once
////////////////////////////////////////////////////
// channel
////////////////////////////////////////////////////

namespace zn
{
    class Channel
    {
    public:
        Channel() : fmod( NULL ) {}

        void Stop() { if( fmod ) fmod->stop(); }

        FMOD::Channel* fmod;
    };
}