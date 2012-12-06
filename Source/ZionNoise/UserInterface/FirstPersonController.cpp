////////////////////////////////////////////////////
// first person controller
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "FirstPersonController.h"
#include "..\GameObject\Component\Physics\FirstPersonCharacterComponent.h"
#include "..\Game\Game.h"
#include "..\Window\Window.h"

namespace zn
{
    FirstPersonController::FirstPersonController( float yawInDegrees ) 
        : m_pControlledObject( shared_ptr< FirstPersonCharacterComponent >() ), m_targetYaw( 0.f ),
        m_yaw( 0.f ), m_maxSpeed( 0.f )
    {
        uint16Vec2 mousePos = g_pGame->GetWindow()->GetCursorPos();
        m_mouseLastX = mousePos.x;
        m_mouseLastY = mousePos.y;   
        // reset arrays to false
        memset( m_keyState, 0x00, sizeof( m_keyState ) );
        memset( m_keyOldState, 0x00, sizeof( m_keyOldState ) );
    }

    FirstPersonController::~FirstPersonController()
    {

    }

    bool FirstPersonController::VOnKeyMsg( const Message& msg )
    {
        if( msg == Message::KeyDown )
        {
            m_keyState[msg.key.type] = true;
            return true;
        }
        if( msg == Message::KeyUp )
        {
            m_keyState[msg.key.type] = false;
            return true;
        }
        return false;
    }

    bool FirstPersonController::VOnMouseMsg( const Message& msg )
    {
        if( msg == Message::MouseMove && ( m_mouseLastX != msg.mouseMove.x || m_mouseLastY != msg.mouseMove.y ) )
        {
            m_targetYaw = m_targetYaw + ( m_mouseLastX - msg.mouseMove.x );
            //m_targetPitch = m_targetPitch + ( msg.mouseMove.y - m_mouseLastY );
            m_mouseLastX = msg.mouseMove.x;
            m_mouseLastY = msg.mouseMove.y;
            return true;
        }
        return false;
    }

    void FirstPersonController::Update( const float deltaMs )
    {
        float deltaS = deltaMs * 0.001f;
        if( m_pControlledObject )
        {
            float forwardBack = m_pControlledObject->GetForwardBack();
            float leftRight = m_pControlledObject->GetLeftRight();
            if( m_keyState[Key::W] )
            {
                float numberOfSeconds = 3.f;
                if( forwardBack < m_charInfo.maxRunSpeed )
                {
                    if( forwardBack < 0 )
                        numberOfSeconds = 0.2f;
                    forwardBack += m_charInfo.maxRunSpeed * ( deltaS / numberOfSeconds );
                }
		        if( forwardBack > m_charInfo.maxRunSpeed )
			        forwardBack = m_charInfo.maxRunSpeed;
            }
            if( m_keyState[Key::S] )
            {
                float numberOfSeconds = 1.f;
                if( forwardBack > -m_charInfo.maxBackwardSpeed )
                {
                    if( forwardBack > 0 )
                        numberOfSeconds = 0.2f;
                    forwardBack -= m_charInfo.maxBackwardSpeed * ( deltaS / numberOfSeconds );
                }
		        if( forwardBack < -m_charInfo.maxBackwardSpeed )
			        forwardBack = -m_charInfo.maxBackwardSpeed;
            }
            if( !m_keyState[Key::W] && !m_keyState[Key::S] )
            {
                float numberOfSeconds = 0.2f;
                if( forwardBack > 0 )
                {
                    forwardBack -= m_charInfo.maxRunSpeed * ( deltaS / numberOfSeconds );
                    if( forwardBack < 0 )
                        forwardBack = 0.f;
                }
                else if( forwardBack < 0 )
                {
                    forwardBack += m_charInfo.maxBackwardSpeed * ( deltaS / numberOfSeconds );
                    if( forwardBack > 0 )
                        forwardBack = 0.f;
                }
            }
            if( m_keyState[Key::A] )
            {
                float numberOfSeconds = 1.f;
                if( leftRight < m_charInfo.maxStraffeSpeed )
                {
                    if( leftRight < 0 )
                        numberOfSeconds = 0.2f;
                    leftRight += m_charInfo.maxStraffeSpeed * ( deltaS / numberOfSeconds );
                }
		        if( leftRight > m_charInfo.maxStraffeSpeed )
			        leftRight = m_charInfo.maxStraffeSpeed;
            }
            if( m_keyState[Key::D] )
            {
                float numberOfSeconds = 1.f;
                if( leftRight > -m_charInfo.maxStraffeSpeed )
                {
                    if( leftRight > 0 )
                        numberOfSeconds = 0.2f;
                    leftRight -= m_charInfo.maxStraffeSpeed * ( deltaS / numberOfSeconds );
                }
		        if( leftRight < -m_charInfo.maxStraffeSpeed )
			        leftRight = -m_charInfo.maxStraffeSpeed;
            }
            if( !m_keyState[Key::A] && !m_keyState[Key::D] )
            {
                float numberOfSeconds = 0.2f;
                if( leftRight > 0 )
                {
                    leftRight -= m_charInfo.maxStraffeSpeed * ( deltaS / numberOfSeconds );
                    if( leftRight < 0 )
                        leftRight = 0.f;
                }
                else if( leftRight < 0 )
                {
                    leftRight += m_charInfo.maxStraffeSpeed * ( deltaS / numberOfSeconds );
                    if( leftRight > 0 )
                        leftRight = 0.f;
                }
            }
            if( m_keyState[Key::Space] )
            {
                m_pControlledObject->SetJump( true );
            }
            else
            {
                m_pControlledObject->SetJump( false );
            }
            m_pControlledObject->SetForwardBack( forwardBack );
            m_pControlledObject->SetLeftRight( leftRight );

            {
                float angle = ( m_targetYaw - m_yaw ) * ( .35f );
                m_yaw += angle;
                m_pControlledObject->Rotate( fVec3::up, Math::DegreesToRadians( -angle ) );
            }
        }
    }

    void FirstPersonController::SetControlledObject( shared_ptr< FirstPersonCharacterComponent > pFirstPersonComp )
    {
        m_pControlledObject = pFirstPersonComp;
        m_charInfo = m_pControlledObject->GetCharInfo();
    }
}