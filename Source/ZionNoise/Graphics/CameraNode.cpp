////////////////////////////////////////////////////
// Camera node
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "CameraNode.h"
#include "Scene.h"

namespace zn
{
    CameraNode::CameraNode( const Mat4x4* pTransform, const Frustum& frustum )
        : SceneNode( NO_GAME_OBJECT_ID, NULL, RenderPass::First, pTransform ), m_frustum( frustum ), 
        m_camOffset( 0.0f, 1.0f, -10.0f, 0.0f ), m_pTarget( shared_ptr< SceneNode >() )
    {

    }

    void CameraNode::Init()
    {
        m_frustum.Init( ZN_PI / 4.f, 
            g_pGame->GetWindowSize().x / static_cast< float >( g_pGame->GetWindowSize().y ), 0.001f, 1000.f );
        g_pGame->GetRenderer()->CreateMatrixPerspectiveFovLH( &m_projection, m_frustum.GetFieldOfView(), 
            m_frustum.GetAspectRatio(), m_frustum.GetNearClipDist(), m_frustum.GetFarClipDist() );
    }

    void CameraNode::VUpdate( Scene* pScene, const float deltaMs )
    {
        if( m_pTarget )
        {
            Mat4x4 mat = m_pTarget->GetToWorldNoScale();
		    fVec4 atWorld = mat.Transform( m_camOffset );
		    fVec3 pos = mat.GetPosition() + fVec3( atWorld.x, atWorld.y, atWorld.z );
		    mat.SetPosition( pos );
		    SetTransform( &mat );
            /*Mat4x4 mat = m_pTarget->GetToWorldNoScale();
		    fVec4 atWorld = mat.Transform( m_camOffset );
            fVec3 target = mat.GetPosition();
		    fVec3 pos = target + fVec3( atWorld.x, atWorld.y, atWorld.z );
            Mat4x4 newTransform;
            Geometry::MatrixLookAtLH( &newTransform, pos, target, fVec3::up );
		    SetTransform( &newTransform );*/
        }
    }
}