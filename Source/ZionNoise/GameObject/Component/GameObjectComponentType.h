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
            Mesh
        };
    }
}