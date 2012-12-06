#pragma once
////////////////////////////////////////////////////
// audio component base
////////////////////////////////////////////////////

#include "IGameObjectComponent.h"
#include "..\..\Audio\Channel.h"
#include "..\..\Audio\Sound.h"

namespace zn
{
    class AudioComponent : public IGameObjectComponent
    {
    public:
        AudioComponent();
        ~AudioComponent();

        void Play();

        bool VInit();

        void SetFilename( const string& filename ) { m_filename = filename; }

    private:
	    string m_filename;
	    //The sound we are playing
	    Sound* m_pSound;
	    //channel to control the sound
	    Channel* m_pChannel;
    };
}