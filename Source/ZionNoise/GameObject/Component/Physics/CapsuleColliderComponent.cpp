#pragma once
////////////////////////////////////////////////////
// capsule collider component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "CapsuleColliderComponent.h"
#include "..\..\GameObject.h"

namespace zn
{
    CapsuleColliderComponent::CapsuleColliderComponent()
         : ColliderComponent( GameObjectComponent::MeshCollider )
    {

    }

    CapsuleColliderComponent::~CapsuleColliderComponent()
    {

    }

    bool CapsuleColliderComponent::VInit()
    {
        if( !m_pPhysicsShape )
        {
		    hkVector4 vertexA( m_vertexA.x, m_vertexA.y, m_vertexA.z );
		    hkVector4 vertexB( m_vertexB.x, m_vertexB.y, m_vertexB.z );
		    // creates a capsule with a axis between "start" and "end", and the specified "radius"
		    m_pPhysicsShape = new hkpCapsuleShape( vertexA, vertexB, m_radius );
            return true;
	    }
        return false;
    }
}