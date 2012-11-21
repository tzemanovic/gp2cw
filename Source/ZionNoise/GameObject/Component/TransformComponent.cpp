////////////////////////////////////////////////////
// transform component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "TransformComponent.h"

namespace zn
{
    TransformComponent::TransformComponent() : IGameObjectComponent( GameObjectComponent::Transform )
    {
        Mat4x4::Identity( &m_transform );
    }
}