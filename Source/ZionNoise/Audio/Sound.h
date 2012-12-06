#pragma once
////////////////////////////////////////////////////
// sound
////////////////////////////////////////////////////

namespace zn
{
    class Sound
    {
    public:
        Sound() : fmod( NULL ) {}
        
        void Release() { if( fmod ) fmod->release(); fmod = NULL; }

        FMOD::Sound* fmod;
    };
}