////////////////////////////////////////////////////
// rigid body component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "..\TransformComponent.h"
#include "..\..\GameObject.h"
#include "BoxColliderComponent.h"
#include "MeshColliderComponent.h"
#include "CapsuleColliderComponent.h"
#include "..\..\..\Physics\Physics.h"

namespace zn
{
    RigidBodyComponent::RigidBodyComponent( bool isFixed, float mass ) 
        : IGameObjectComponent( GameObjectComponent::RigidBody ), m_pRigidBody( NULL ), m_mass( mass ),
        m_isFixed( isFixed )
    {

    }

    RigidBodyComponent::~RigidBodyComponent()
    {
        if( m_pRigidBody )
	    {
		    m_pRigidBody->removeReference();
	    }
    }

    bool RigidBodyComponent::VInit()
    {
        //Grab the transform
	    shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( m_pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
        if( pTransformComponent )
        {
            //grab the collider. If we have one, then initialise
            shared_ptr< ColliderComponent > pColliderComponent = MakeStrongPtr( m_pGameObject->GetComponent< BoxColliderComponent >( GameObjectComponent::BoxCollider ) );
	        if( !pColliderComponent )
                pColliderComponent = MakeStrongPtr( m_pGameObject->GetComponent< MeshColliderComponent >( GameObjectComponent::MeshCollider ) );
            if( !pColliderComponent )
                pColliderComponent = MakeStrongPtr( m_pGameObject->GetComponent< CapsuleColliderComponent >( GameObjectComponent::CapsuleCollider ) );
            if( !pColliderComponent )
                return false;

            if ( !pColliderComponent->IsShapeCreated() )
            {
		        if ( !pColliderComponent->VInit() )
                {
                    return false;
                }
            }

	        // Create the rigid body info
	        hkpRigidBodyCinfo rigidBodyInfo;
	        if( m_isFixed )
		        rigidBodyInfo.m_motionType=hkpMotion::MOTION_FIXED;

	        // associate the shape with the rigid body
	        rigidBodyInfo.m_shape = pColliderComponent->GetPhysicsShape();
	        // Calculate the mass using the shape and the mass of the object
	        hkpInertiaTensorComputer::setShapeVolumeMassProperties( pColliderComponent->GetPhysicsShape(), m_mass, rigidBodyInfo );

	        //Create the rigid body
	        m_pRigidBody = new hkpRigidBody( rigidBodyInfo );

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

            // add to the world
            Physics::Get()->AddEntity( m_pGameObject->GetId(), this );

            return true;
        }
        return false;
    }

    /*void RigidBodyComponent::VUpdate( float deltaMs )
    {
        //Get the transform component
	    shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( m_pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
        //If we have a rigid body
        if( !pTransformComponent )
        {
		    //get the current position and rotation of the rigid body
		    hkVector4 pos = m_pRigidBody->getPosition();
		    hkQuaternion rot = m_pRigidBody->getRotation();
		    //Set the position and rotation of the transform
            Mat4x4 transform = pTransformComponent->GetTransform();
		    transform->setPosition(pos.getComponent(0),pos.getComponent(1),pos.getComponent(2));
		    transform->setRotation(rot.m_vec.getComponent(0),rot.m_vec.getComponent(1),
			    rot.m_vec.getComponent(2),rot.m_vec.getComponent(3));
	    }
    }*/

    fVec3 RigidBodyComponent::GetPosition()
    {
        hkVector4 hkPos = m_pRigidBody->getPosition();
        fVec3 pos( hkPos.getComponent( 0 ), hkPos.getComponent( 1 ), hkPos.getComponent( 2 ) );
        return pos;
    }

    Quaternion RigidBodyComponent::GetRotation()
    {
        hkQuaternion hkRot = m_pRigidBody->getRotation();
        Quaternion rot( hkRot.m_vec.getComponent( 0 ), hkRot.m_vec.getComponent( 1 ), 
            hkRot.m_vec.getComponent( 2 ), hkRot.m_vec.getComponent( 3 ) );
        return rot;
    }
}