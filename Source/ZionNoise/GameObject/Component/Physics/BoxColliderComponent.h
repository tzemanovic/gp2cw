#pragma once
////////////////////////////////////////////////////
// box collider component
////////////////////////////////////////////////////

#include "ColliderComponent.h"

namespace zn
{
    class BoxColliderComponent : public ColliderComponent
    {
    public:
        BoxColliderComponent( const fVec3& size );
        ~BoxColliderComponent();

        bool VInit();
    private:
	    fVec3 m_halfSize;
    };
}