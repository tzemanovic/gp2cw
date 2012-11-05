#pragma once
////////////////////////////////////////////////////
// view interface
////////////////////////////////////////////////////

namespace zn
{
    typedef uint32 ViewId;
    class IView
    {
    public:
        virtual ~IView() {}

        void Attach( uint32 viewId, GameObjectId gameObjectId )
        {
            m_viewId = viewId;
            m_owner = gameObjectId;
        }

        virtual void VRender( float deltaMs ) = 0;
        virtual void VUpdate( float deltaMs ) = 0;

    protected:
        ViewId m_viewId;
        GameObjectId m_owner;
    };
}