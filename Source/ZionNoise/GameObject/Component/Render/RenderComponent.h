#pragma once
////////////////////////////////////////////////////
// render component base
////////////////////////////////////////////////////

#include "..\IGameObjectComponent.h"

namespace zn
{
    class SceneNode;

    class RenderComponent : public IGameObjectComponent
    {
    public:
        RenderComponent( GameObjectComponentType type );

        virtual bool VInit();

    protected:
        shared_ptr< SceneNode > VGetSceneNode();

        virtual shared_ptr< SceneNode > VCreateSceneNode() = 0;

        shared_ptr< SceneNode > m_pSceneNode;
    };
}