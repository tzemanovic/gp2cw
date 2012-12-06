////////////////////////////////////////////////////
// audio manager
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "AudioManager.h"

namespace zn
{
    AudioManager::AudioManager() : m_pAudioSystem( NULL )
    {

    }

    AudioManager::~AudioManager()
    {
        if( m_pAudioSystem )
	    {
		    m_pAudioSystem->release();
		    m_pAudioSystem = 0;
	    }
    }

    void AudioManager::Init()
    {
        //This setup is directly taken from the Getting Started with FMOD for Windows
	    //Page 8 titled - Recommended startup sequence (IMPORTANT!)
	    //temp values
	    FMOD_RESULT result;
	    //version of FMD
	    unsigned int version;
	    //number of audio drivers
	    int numdrivers;
	    //speaker mode
	    FMOD_SPEAKERMODE speakermode;
	    //The capabilities of the audio device
	    FMOD_CAPS caps;
	    //holds the name of the driver
	    char name[256];

	    //Create audio system
	    result = FMOD::System_Create( &m_pAudioSystem );
	
	    //check version
	    result = m_pAudioSystem->getVersion( &version );
	    if( version < FMOD_VERSION )
	    {
		    //Wrong version of FMOD
		    return;
	    }
	    //Get number of drivers
	    result = m_pAudioSystem->getNumDrivers( &numdrivers );
	    if( numdrivers == 0 )
	    {
		    result = m_pAudioSystem->setOutput( FMOD_OUTPUTTYPE_NOSOUND );
	    }
	    else
	    {
		    //Get driver caps and speaker mode, this will get the setup of the speakers
		    //from the OS
		    result = m_pAudioSystem->getDriverCaps( 0, &caps, 0, &speakermode );
		    result = m_pAudioSystem->setSpeakerMode( speakermode );
		    if( caps & FMOD_CAPS_HARDWARE_EMULATED )
		    {
			    /*
			    The user has the 'Acceleration' slider set to off! This is really bad
			    for latency! You might want to warn the user about this.
			    */
			    result = m_pAudioSystem->setDSPBufferSize( 1024, 10 );
		    }
		    //get the driver name
		    result = m_pAudioSystem->getDriverInfo( 0, name, 256, 0 );
		    if( strstr( name, "SigmaTel" ) )
		    {
			    /*
			    Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
			    PCM floating point output seems to solve it.
			    */
			    result = m_pAudioSystem->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, 
                    FMOD_DSP_RESAMPLER_LINEAR );
		    }
		    //finally init FMOD
		    result = m_pAudioSystem->init( 100, FMOD_INIT_NORMAL, 0 );
		    if ( result == FMOD_ERR_OUTPUT_CREATEBUFFER )
		    {
			    /*
			    Ok, the speaker mode selected isn't supported by this soundcard. Switch it
			    back to stereo...
			    */
			    result = m_pAudioSystem->setSpeakerMode( FMOD_SPEAKERMODE_STEREO );
			    /*
			    ... and re-init.
			    */
			    result = m_pAudioSystem->init( 100, FMOD_INIT_NORMAL, 0 );
		    }
	    }
    }

    void AudioManager::Update()
    {
        if( m_pAudioSystem )
            m_pAudioSystem->update();
    }

    Sound* AudioManager::LoadSound( const string& filename, bool stream, bool isLooped, bool is3D )
    {
        //load or stream sound
	    FMOD_RESULT result;
        Sound* pSound = ZN_NEW Sound();
        FMOD_MODE mode =  ( is3D ? FMOD_3D : FMOD_2D ) | ( isLooped ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF ) | FMOD_HARDWARE;
	    if (stream)
            result = m_pAudioSystem->createSound( filename.c_str(), mode, 0, &pSound->fmod );
	    else
            result = m_pAudioSystem->createStream( filename.c_str(), mode, 0, &pSound->fmod );
	    return pSound;
    }

    //Number of times to loop before stopping. 0 = oneshot. 1 = loop once then stop. -1 = loop forever. Default = -1 
    Channel* AudioManager::PlaySound( const Sound* pSound, const int32 loopCount )
    {
        //play sound, return a channel so we can control the sound
	    //while its playing
	    Channel* pChannel = ZN_NEW Channel();
	    m_pAudioSystem->playSound( FMOD_CHANNEL_FREE, pSound->fmod, false, &pChannel->fmod );
        pChannel->fmod->setLoopCount( loopCount );

	    return pChannel;
    }

    void AudioManager::UpdateListener( const fVec3& position, const fVec3& velocity, const fVec3& forward, 
        const fVec3& up )
    {
        if( m_pAudioSystem )
        {
            FMOD_VECTOR pos;
	        FMOD_VECTOR vel;
	        FMOD_VECTOR forw;
	        FMOD_VECTOR upw;

            pos.x = position.x;
            pos.y = position.y;
            pos.z = position.z;
            vel.x = velocity.x;
            vel.y = velocity.y;
            vel.z = velocity.z;
            forw.x = forward.x;
            forw.y = forward.y;
            forw.z = forward.z;
            upw.x = up.x;
            upw.y = up.y;
            upw.z = up.z;

            //update the listener
	        m_pAudioSystem->set3DListenerAttributes( 0, &pos, &vel, &forw, &upw );
        }
    }
}