#pragma once
////////////////////////////////////////////////////
// game object component types
////////////////////////////////////////////////////

namespace zn
{
    typedef uint16 GameObjectComponentType; 
    namespace GameObjectComponent
    {
        enum
        {
            Transform,
            Mesh,
            SkySphere,
            BoxCollider,
            SphereCollider,
            CapsuleCollider,
            CylinderCollider,
            MeshCollider,
            RigidBody,
            Count
        };
    }
}