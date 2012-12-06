////////////////////////////////////////////////////
// box collider component
////////////////////////////////////////////////////

#include "zionNoiseStd.h"
#include "BoxColliderComponent.h"

namespace zn
{
    BoxColliderComponent::BoxColliderComponent( const fVec3& size ) 
        : ColliderComponent( GameObjectComponent::BoxCollider )
    {
        m_halfSize = size / 2.f;  
    }

    BoxColliderComponent::~BoxColliderComponent()
    {

    }

    bool BoxColliderComponent::VInit()
    {
        if( !m_pPhysicsShape )
        {
            hkVector4 halfExtent( m_halfSize.x, m_halfSize.y, m_halfSize.z );
		    m_pPhysicsShape = new hkpBoxShape( halfExtent, 0.0f );
	    }
        return true;
    }
}