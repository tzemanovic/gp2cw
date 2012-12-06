#pragma once
////////////////////////////////////////////////////
// capsule collider component
////////////////////////////////////////////////////

#include "ColliderComponent.h"

namespace zn
{
    class CapsuleColliderComponent : public ColliderComponent
    {
    public:
        CapsuleColliderComponent();
        ~CapsuleColliderComponent();

        bool VInit();
    private:
        float m_radius;
        fVec3 m_vertexA;
        fVec3 m_vertexB;
    };
}