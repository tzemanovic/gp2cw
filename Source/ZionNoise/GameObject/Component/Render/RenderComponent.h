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

        virtual shared_ptr< SceneNode > VCreateSceneNode() = 0;
        virtual const float VCalculateBoudingSphereRadius() = 0;

        shared_ptr< SceneNode > m_pSceneNode;

    private:
        shared_ptr< SceneNode > VGetSceneNode();

    };
}