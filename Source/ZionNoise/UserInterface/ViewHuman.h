#pragma once
////////////////////////////////////////////////////
// human view interface
////////////////////////////////////////////////////

#include "..\Utilities\IView.h"
#include "ScreenElementScene.h"

namespace zn
{
    class Renderer;
    class IScreenElement;
    class CameraNode;

    typedef std::list< shared_ptr< IScreenElement > > ScreenElementList;

    class ViewHuman : public IView
    {
    public:
        ViewHuman();
        ~ViewHuman();

        void SetRenderer( shared_ptr< Renderer > pRenderer );
        void Init();

        virtual void VRender( const float deltaMs );
        virtual void VUpdate( const float deltaMs );
        virtual const bool VProcessMessage( const Message& message );
        virtual void VAddSceneNode( shared_ptr< SceneNode > pSceneNode );

    private:
        shared_ptr< ScreenElementScene > m_pScene;
        shared_ptr< Renderer > m_pRenderer;
        shared_ptr< CameraNode > m_pCamera;
        float m_nextRender;
        ScreenElementList m_screenElements;
    };
}