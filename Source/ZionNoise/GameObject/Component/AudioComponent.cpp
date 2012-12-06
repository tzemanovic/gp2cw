////////////////////////////////////////////////////
// audio component base
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "AudioComponent.h"
#include "..\..\Audio\AudioManager.h"

namespace zn
{
    AudioComponent::AudioComponent() : IGameObjectComponent( GameObjectComponent::Audio ), 
        m_filename( "" ), m_pSound( NULL ), m_pChannel( NULL )
    {
        
    }

    AudioComponent::~AudioComponent()
    {
        //ZN_SAFE_RELEASE( m_pSound );
    }

    void AudioComponent::Play()
    {
        if( m_pSound )
        {
            // only play if is not playing
            if( m_pChannel )
            {
                bool isPlaying;
                m_pChannel->fmod->isPlaying( &isPlaying );
                if( isPlaying )
                    return;
            }
            m_pChannel = AudioManager::Get()->PlaySound( m_pSound, 0 );
        }
    }
    
    bool AudioComponent::VInit()
    {
        if( !m_filename.empty() )
        {
            //Create the sound
	        m_pSound = AudioManager::Get()->LoadSound( m_filename, false, false, true );
            return true;
        }
        return false;
    }
}