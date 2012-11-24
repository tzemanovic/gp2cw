#pragma once
////////////////////////////////////////////////////
// Sky scene node
////////////////////////////////////////////////////

#include "SceneNode.h"

namespace zn
{
    class SkySceneNode : public SceneNode
    {
    public:
        SkySceneNode( const GameObjectId gameObjectId, RenderComponent* pRenderComponent ) 
            : SceneNode( gameObjectId, pRenderComponent, RenderPass::Sky, &Mat4x4::identity ) {}

        bool VIsVisible( Scene *pScene ) const { return true; }
    };
}