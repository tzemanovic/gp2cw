#pragma once
////////////////////////////////////////////////////
// mesh collider component
////////////////////////////////////////////////////

#include "ColliderComponent.h"

namespace zn
{
    class MeshColliderComponent : public ColliderComponent
    {
    public:
        MeshColliderComponent();
        ~MeshColliderComponent();

        bool VInit();
    private:
        float* m_pVerts;
        uint32 m_vertCount;        
    };
}