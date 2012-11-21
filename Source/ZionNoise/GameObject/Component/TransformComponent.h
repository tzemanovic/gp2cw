#pragma once
////////////////////////////////////////////////////
// transform component
////////////////////////////////////////////////////

#include "IGameObjectComponent.h"

namespace zn
{
    class TransformComponent : public IGameObjectComponent
    {
    public:
        TransformComponent();

        const fVec3 GetPosition() const { m_transform.GetPosition(); }
        void SetPosition( const fVec3& pos ) { m_transform.SetPosition( pos ); }
        const Mat4x4 GetTransform() const { return m_transform; }

    private:
        Mat4x4 m_transform;
    };
}