#pragma once
////////////////////////////////////////////////////
// Camera node
////////////////////////////////////////////////////

#include "SceneNode.h"

namespace zn
{
    class Scene;

    class CameraNode : public SceneNode
    {
    public:
        CameraNode( const Mat4x4* pTransform, const Frustum& frustum );

        void Init();

        const Frustum& GetFrustum() { return m_frustum; }
        Mat4x4& GetProjection() { return m_projection; }
        Mat4x4& GetView() { return m_fromWorld; }
        
    protected:
        Frustum m_frustum;
        Mat4x4 m_projection;
    };
}