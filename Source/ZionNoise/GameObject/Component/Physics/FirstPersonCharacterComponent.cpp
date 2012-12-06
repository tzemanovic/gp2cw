////////////////////////////////////////////////////
// character rigid body component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "FirstPersonCharacterComponent.h"
#include "..\..\..\Physics\Physics.h"
#include "..\..\GameObject.h"
#include "..\TransformComponent.h"

namespace zn
{
    FirstPersonCharacterComponent::FirstPersonCharacterComponent( const CharacterControllerInfo& cInfo )
        : RigidBodyComponent( false, cInfo.mass ), m_charInfo( cInfo ), m_currentTime( 0.f ), 
        m_forwardBack( 0.f ), m_leftRight( 0.f )
    {
        m_type = GameObjectComponent::FirstPersonCharacter;	    
    }

    FirstPersonCharacterComponent::~FirstPersonCharacterComponent()
    {
        m_pCharacterRigidBody->removeReference();
    }

    bool FirstPersonCharacterComponent::VInit()
    {
        //Grab the transform
        shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( m_pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
        if( pTransformComponent )
        {

            hkpCharacterRigidBodyCinfo charCInfo;
            charCInfo.m_shape = new hkpCapsuleShape( hkVector4::getZero(),
                hkVector4( 0.0f, m_charInfo.capsuleHeight, 0.0f ), m_charInfo.capsuleRadius );
            charCInfo.m_mass = m_charInfo.mass;
            charCInfo.m_maxLinearVelocity = m_charInfo.maxRunSpeed;
            //m_charCInfo.m_maxForce = cInfo.maxPushForce;
            //m_charCInfo.m_maxLinearVelocity = cInfo.maxRunSpeed;
            //m_charCInfo.m_friction = 0.5f;

            m_pCharacterRigidBody = new hkpCharacterRigidBody( charCInfo );
            // Create the Character state machine and context.
            hkpCharacterState* state;
            m_pStateManager = new hkpCharacterStateManager();

            m_pRigidBody = m_pCharacterRigidBody->getRigidBody();
            //Assign user data
            m_pRigidBody->setUserData( hkUlong( m_pGameObject->GetId() ) );

            //pos and rotate the rigid body to match our object
            fVec3 pos = pTransformComponent->GetPosition();
            Quaternion rot = pTransformComponent->GetRotation();
            hkVector4 hkPos( pos.x, pos.y, pos.z );
            hkQuaternion hkRot( rot.x, rot.y, rot.z, rot.w );
            hkRot.normalize();
            m_pRigidBody->setPosition( hkPos );
            m_pRigidBody->setRotation( hkRot );
            Mat4x4 trans = pTransformComponent->GetTransformNoScale();
            fVec4 forward( fVec4::forward );
            forward = trans.Transform( forward );

            state = new hkpCharacterStateOnGround();
            static_cast< hkpCharacterStateOnGround* >( state )->setSpeed( m_charInfo.maxRunSpeed );
            m_pStateManager->registerState( state, HK_CHARACTER_ON_GROUND );
            state->removeReference();

            state = new hkpCharacterStateInAir();
            static_cast< hkpCharacterStateInAir* >( state )->setSpeed( m_charInfo.airSpeed );
            m_pStateManager->registerState( state, HK_CHARACTER_IN_AIR );
            state->removeReference();

            state = new hkpCharacterStateJumping();
            static_cast< hkpCharacterStateJumping* >( state )->setJumpHeight( m_charInfo.jumpHeight );
            m_pStateManager->registerState( state, HK_CHARACTER_JUMPING );
            state->removeReference();

            m_pCharacterContext = new hkpCharacterContext( m_pStateManager, HK_CHARACTER_IN_AIR );
            m_pStateManager->removeReference();

            // Set character type
            m_pCharacterContext->setCharacterType( hkpCharacterContext::HK_CHARACTER_RIGIDBODY );

            hkpFirstPersonCharacterCinfo fpsCinfo;
            fpsCinfo.m_capsuleHeight = m_charInfo.capsuleHeight;
            fpsCinfo.m_capsuleRadius = m_charInfo.capsuleRadius;
            fpsCinfo.m_characterRb = m_pCharacterRigidBody;
            fpsCinfo.m_context = m_pCharacterContext;
            fpsCinfo.m_eyeHeight = m_charInfo.eyeHeight;
            fpsCinfo.m_world =  Physics::Get()->GetWorld();

            fpsCinfo.m_position.setZero();
            fpsCinfo.m_direction.set( 0.0f, 0.0f, 1.0f );
            fpsCinfo.m_gravityStrength = m_charInfo.gravityStrength;
            fpsCinfo.m_maxUpDownAngle = ZN_PI * 0.4f;
            fpsCinfo.m_up.set( forward.x, forward.y, forward.z, forward.w );

            m_pFirstPersonCharacter = new hkpFirstPersonCharacter( fpsCinfo );
            m_pCharacterRigidBody->m_unweldingHeightOffsetFactor = 2.0f;
            m_pCharacterRigidBody->m_maxSlopeCosine = cosf( Math::DegreesToRadians( 80.0f ) );

            fpsCinfo.m_world->markForWrite();
            Physics::Get()->AddEntity( m_pGameObject->GetId(), this );

            hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
            m_pCharacterRigidBody->setListener( listener );
            listener->removeReference();

            fpsCinfo.m_world->unmarkForWrite();
            return true;
        }
        return false;
    }

    void FirstPersonCharacterComponent::VUpdate( const float deltaMs )
    {
        m_currentTime += deltaMs;
        if( m_currentTime >= PHYSICS_UPDATE_TIME )
        {
            hkpWorld* world = Physics::Get()->GetWorld();
	        world->markForWrite();
            
            fVec4 forward( fVec4::forward );
            shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( m_pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
            if( pTransformComponent )
            {
                Mat4x4 trans = pTransformComponent->GetTransformNoScale();
                forward = trans.Transform( forward );
            }

            hkVector4 forwardDirection( forward.x, forward.y, forward.z, forward.w );
            
	        hkpFirstPersonCharacter::CharacterControls controls;
	        controls.m_fire = false;
	        controls.m_fireRmb = false;
	        controls.m_forward = forwardDirection;
	        controls.m_forwardBack = -m_forwardBack;
	        controls.m_straffeLeftRight = -m_leftRight;
	        controls.m_wantJump = m_jump;

	        m_pFirstPersonCharacter->update( PHYSICS_UPDATE_TIME * 0.001f, controls );

	        world->unmarkForWrite();
            m_currentTime = 0.f;
        }
    }

    void FirstPersonCharacterComponent::Rotate( const fVec3& axis, const float angleRad )
    {
        Quaternion rot;
        Geometry::QuaternionRotationAxis( &rot, axis, angleRad );
        shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( m_pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
        if( pTransformComponent )
        {
            pTransformComponent->Rotate( rot );
            Quaternion newRot = pTransformComponent->GetRotation();
            hkQuaternion hkRot( newRot.x, newRot.y, newRot.z, newRot.w );
            hkRot.normalize();
            GetRigidBody()->setRotation( hkRot );
        }
    }
}