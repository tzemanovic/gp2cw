#pragma once
////////////////////////////////////////////////////
// root scene node
////////////////////////////////////////////////////

#include "SceneNode.h"

namespace zn
{
    class RootSceneNode : public SceneNode
    {
    public:
        RootSceneNode();

        void VAddChild( shared_ptr< SceneNode > pSceneNode );
        void VRenderChildren( Scene *pScene );

        bool VIsVisible( Scene *pScene ) const { return true; }
    };
}