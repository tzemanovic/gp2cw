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

        //void VAddChild( shared_ptr< SceneNode > pSceneNode ); // override this when the render passes are implemented
        //void VRenderChildren( Scene *pScene ); // override this when the render passes are implemented

        bool VIsVisible( Scene *pScene ) const { return true; }
    };
}