////////////////////////////////////////////////////
// mouse handler interface
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "MovementController.h"
#include "..\Graphics\SceneNode.h"
#include "..\Window\Window.h"

namespace zn
{
    MovementController::MovementController( shared_ptr< SceneNode > pControlledObject, float yawInDegrees, float pitchInDegrees ) 
        : m_pControlledObject( pControlledObject )
    {
        m_pControlledObject->GetTransform( &m_toWorld, &m_fromWorld );

        m_targetYaw = m_yaw = Math::RadiansToDegrees( -yawInDegrees );
        m_targetPitch = m_pitch = Math::DegreesToRadians( pitchInDegrees );
        m_maxSpeed = 10.f;
        m_currentSpeed = 0.f;
        fVec3 pos = m_toWorld.GetPosition();
        m_position = Mat4x4::identity;
        m_position.SetPosition( pos );

        uint16Vec2 mousePos = g_pGame->GetWindow()->GetCursorPos();
        m_mouseLastX = mousePos.x;
        m_mouseLastY = mousePos.y;
        
        memset( m_keyState, 0x00, sizeof( m_keyState ) );
        memset( m_keyOldState, 0x00, sizeof( m_keyOldState ) );
    }

    MovementController::~MovementController()
    {
        m_pControlledObject.reset();
    }

    bool MovementController::VOnKeyMsg( const Message& msg )
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

    bool MovementController::VOnMouseMsg( const Message& msg )
    {
        if( msg == Message::MouseMove && ( m_mouseLastX != msg.mouseMove.x || m_mouseLastY != msg.mouseMove.y ) )
        {
            m_targetYaw = m_targetYaw + ( m_mouseLastX - msg.mouseMove.x );
            m_targetPitch = m_targetPitch + ( msg.mouseMove.y - m_mouseLastY );
            m_mouseLastX = msg.mouseMove.x;
            m_mouseLastY = msg.mouseMove.y;
            return true;
        }
        return false;
    }

    void MovementController::Update( const float deltaMs )
    {
        bool translating = false;
	    fVec4 xTranslation( 0, 0, 0, 0 );
	    fVec4 yTranslation( 0, 0, 0, 0 );
	    fVec4 zTranslation( 0, 0, 0, 0 );
        
        if( m_keyState[Key::W] || m_keyState[Key::S] )
        {
            zTranslation = fVec4::forward;
            if( m_keyState[Key::S] )
            {
                zTranslation *= -1.f;
            }
            zTranslation = m_toWorld.Transform( zTranslation );
            translating = true;
        }
        else if( m_keyState[Key::A] || m_keyState[Key::D] )
        {
            xTranslation = fVec4::right;
            if( m_keyState[Key::A] )
            {
                xTranslation *= -1.f;
            }
            xTranslation = m_toWorld.Transform( xTranslation );
            translating = true;
        }

        m_yaw += (m_targetYaw - m_yaw) * ( .35f );
        m_targetPitch = Math::Maxf( -90, Math::Minf( 90, m_targetPitch ) );
        m_pitch += (m_targetPitch - m_pitch) * ( .35f );

        // Calculate the new rotation matrix from the camera yaw and pitch
        Mat4x4 matRot;
        matRot.BuildYawPitchRoll( Math::DegreesToRadians( -m_yaw ), Math::DegreesToRadians( m_pitch ), 0 );

        // Create the new object-to-world matrix, and the new world-to-object matrix
        m_toWorld = matRot * m_position;
        m_fromWorld = m_toWorld.Inverse(); 
        m_pControlledObject->SetTransform( &m_toWorld, &m_fromWorld );

        if( translating )
        {
            fVec4 direction4 = xTranslation + yTranslation + zTranslation;
            fVec3 direction( direction4.x, direction4.y, direction4.z );
            fVec3::Normalize( &direction );
            float elapsedTime = deltaMs / 1000.0f;
            float numberOfSeconds = 5.f;
            if( m_currentSpeed < m_maxSpeed )
                m_currentSpeed += m_maxSpeed * ( ( elapsedTime * elapsedTime ) / numberOfSeconds);
		    if( m_currentSpeed > m_maxSpeed )
			    m_currentSpeed = m_maxSpeed;

		    direction *= m_currentSpeed;

            fVec3 pos = m_position.GetPosition() + direction;
		    m_position.SetPosition( pos );
		    m_toWorld.SetPosition( pos );

		    m_fromWorld = m_toWorld.Inverse();
            m_pControlledObject->SetTransform( &m_toWorld, &m_fromWorld );
        }
        else
        {
            m_currentSpeed = 0.f;
        }

        memcpy( m_keyOldState, m_keyState, sizeof( m_keyState ) );
    }
} 