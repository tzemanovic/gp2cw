#pragma once
////////////////////////////////////////////////////
// audio manager
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "Sound.h"
#include "Channel.h"

namespace zn
{
    class AudioManager : private INoCopy
    {
    public:
        ~AudioManager();

        static AudioManager* Get()
        {
            static AudioManager instance;
            return &instance;
        }

        void Init();
        void Update();
	    //load sound, should it be a streaming sound(music)
	    Sound* LoadSound( const string& filename, bool stream, bool isLooped = false, bool is3D = true );
	    //play sound, return the channel which can control the system
	    Channel* PlaySound( const Sound* pSound, const int32 loopCount = -1 );
        //update listener position
        void UpdateListener( const fVec3& position, const fVec3& velocity, const fVec3& forward, const fVec3& up );

    private:
        AudioManager();

	    FMOD::System* m_pAudioSystem;
    };
}