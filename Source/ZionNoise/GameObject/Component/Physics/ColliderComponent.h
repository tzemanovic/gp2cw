#pragma once
////////////////////////////////////////////////////
// collider component base
////////////////////////////////////////////////////

#include "..\IGameObjectComponent.h"

namespace zn
{
    class ColliderComponent : public IGameObjectComponent
    {
    public:
        ColliderComponent( GameObjectComponentType type );
        virtual ~ColliderComponent();

        hkpConvexShape* GetPhysicsShape() const { return m_pPhysicsShape; }
        bool IsShapeCreated()
	    {
		    //if this has a value return true else false
		    return ( m_pPhysicsShape ? true : false );
	    };
    protected:
        hkpConvexShape* m_pPhysicsShape;
    };
}