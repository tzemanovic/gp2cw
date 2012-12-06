////////////////////////////////////////////////////
// root scene node
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "RootSceneNode.h"

namespace zn
{
    RootSceneNode::RootSceneNode() : SceneNode( NO_GAME_OBJECT_ID, NULL, RenderPass::First, &Mat4x4::identity )
    {
        m_children.reserve( RenderPass::Count );

        shared_ptr< SceneNode > pFirstGroup( ZN_NEW SceneNode( NO_GAME_OBJECT_ID, NULL, RenderPass::First, &Mat4x4::identity ) );
        SceneNode::VAddChild( pFirstGroup );
	    shared_ptr< SceneNode > pSkyGroup( ZN_NEW SceneNode( NO_GAME_OBJECT_ID, NULL, RenderPass::Sky, &Mat4x4::identity ) );
	    SceneNode::VAddChild( pSkyGroup );
        shared_ptr< SceneNode > pGameObjectsGroup( ZN_NEW SceneNode( NO_GAME_OBJECT_ID, NULL, RenderPass::GameObjects, &Mat4x4::identity ) );
	    SceneNode::VAddChild( pGameObjectsGroup );
        shared_ptr< SceneNode > pHUDGroup( ZN_NEW SceneNode( NO_GAME_OBJECT_ID, NULL, RenderPass::HUD, &Mat4x4::identity ) );
	    SceneNode::VAddChild( pHUDGroup );
    }

    void RootSceneNode::VAddChild( shared_ptr< SceneNode > pSceneNode )
    {
        RenderPassType renderPass = pSceneNode->GetRenderPass();
        if( renderPass <= RenderPass::Count )
            m_children[renderPass]->VAddChild( pSceneNode );
    }
    
    void RootSceneNode::VRenderChildren( Scene *pScene )
    {
        for( RenderPassType i = RenderPass::First; i < RenderPass::Count; ++i )
        {
            switch( i )
            {
                case RenderPass::Sky:
                case RenderPass::GameObjects:
                case RenderPass::HUD:
                    m_children[i]->VRenderChildren( pScene );
                    break;
            }
        }
    }
}