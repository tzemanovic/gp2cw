////////////////////////////////////////////////////
// Camera node
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "CameraNode.h"
#include "Scene.h"

namespace zn
{
    CameraNode::CameraNode( const Mat4x4* pTransform, const Frustum& frustum )
        : SceneNode( NO_GAME_OBJECT_ID, NULL, RenderPass::First, pTransform ), m_frustum( frustum )
    {

    }

    void CameraNode::Init()
    {
        m_frustum.Init( ZN_PI / 4.f, 
            g_pGame->GetWindowSize().x / static_cast< float >( g_pGame->GetWindowSize().y ), 0.001f, 1000.f );
        g_pGame->GetRenderer()->CreateMatrixPerspectiveFovLH( &m_projection, m_frustum.GetFieldOfView(), 
            m_frustum.GetAspectRatio(), m_frustum.GetNearClipDist(), m_frustum.GetFarClipDist() );
    }
}