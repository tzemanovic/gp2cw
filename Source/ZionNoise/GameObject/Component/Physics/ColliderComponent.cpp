////////////////////////////////////////////////////
// collider component base
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "ColliderComponent.h"

namespace zn
{
    ColliderComponent::ColliderComponent( GameObjectComponentType type ) : IGameObjectComponent( type ),
        m_pPhysicsShape( NULL )
    {

    }

    ColliderComponent::~ColliderComponent()
    {
        if (m_pPhysicsShape)
	    {
		    m_pPhysicsShape->removeReference();
	    }
    }
}