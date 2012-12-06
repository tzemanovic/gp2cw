////////////////////////////////////////////////////
// render component base
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "RenderComponent.h"
#include "..\..\..\Game\Game.h"
#include "..\..\..\Graphics\SceneNode.h"
#include "..\..\GameObject.h"

namespace zn
{
    RenderComponent::RenderComponent( GameObjectComponentType type ) : IGameObjectComponent( type )
    {

    }

    bool RenderComponent::VInit()
    {
        shared_ptr< SceneNode > pSceneNode = VGetSceneNode();
        if( pSceneNode )
        {
            g_pGame->AddSceneNode( m_pGameObject->GetId(), pSceneNode );
            return true;
        }
        return false;
    }

    shared_ptr< SceneNode > RenderComponent::VGetSceneNode()
    {
        if( !m_pSceneNode )
            m_pSceneNode = VCreateSceneNode();
        return m_pSceneNode;
    }
}