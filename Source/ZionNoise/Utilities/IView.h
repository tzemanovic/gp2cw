#pragma once
////////////////////////////////////////////////////
// view interface
////////////////////////////////////////////////////

namespace zn
{
    typedef uint32 ViewId;
    class Message;
    class SceneNode;

    class IView
    {
    public:
        virtual ~IView() {}

        void Attach( uint32 viewId, GameObjectId gameObjectId )
        {
            m_viewId = viewId;
            m_owner = gameObjectId;
        }

        virtual void VRender( const float deltaMs ) = 0;
        virtual void VUpdate( const float deltaMs ) = 0;
        virtual const bool VProcessMessage( const Message& message ) = 0;
        virtual void VAddSceneNode( shared_ptr< SceneNode > pSceneNode ) = 0;

    protected:
        ViewId m_viewId;
        GameObjectId m_owner;
    };
}