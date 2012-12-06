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

        void VUpdate( Scene* pScene, const float deltaMs );

        const Frustum& GetFrustum() { return m_frustum; }
        Mat4x4& GetProjection() { return m_projection; }
        Mat4x4& GetView() { return m_fromWorld; }
        void SetTarget( shared_ptr< SceneNode > pTarget ) { m_pTarget = pTarget; }
        void ClearTarget() { m_pTarget = NULL; }
        void SetOffset( const fVec3& offset ) { m_camOffset = fVec4( offset.x, offset.y, offset.z, 0.f ); }
        
    protected:
        Frustum m_frustum;
        Mat4x4 m_projection;
        fVec4 m_camOffset;
	    shared_ptr< SceneNode > m_pTarget;
    };
}