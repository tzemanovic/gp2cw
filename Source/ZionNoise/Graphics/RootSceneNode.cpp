////////////////////////////////////////////////////
// root scene node
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "RootSceneNode.h"

namespace zn
{
    RootSceneNode::RootSceneNode() : SceneNode( NO_GAME_OBJECT_ID, NULL, &Mat4x4::identity )
    {
        //m_children.reserve( renderPassCount );

    }
}