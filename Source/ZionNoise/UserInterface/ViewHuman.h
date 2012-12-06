#pragma once
////////////////////////////////////////////////////
// human view
////////////////////////////////////////////////////

#include "..\Utilities\IView.h"
#include "ScreenElementScene.h"

namespace zn
{
    class Renderer;
    class IScreenElement;
    class CameraNode;
    class IKeyboardHandler;
    class IMouseHandler;
    class MovementController;

    typedef std::list< shared_ptr< IScreenElement > > ScreenElementList;

    class ViewHuman : public IView
    {
    public:
        ViewHuman();
        virtual ~ViewHuman();

        void SetRenderer( shared_ptr< Renderer > pRenderer );
        void SetCameraOffset( const fVec3& offset );

        virtual void VInit();
        virtual void VRender( const float deltaMs );
        virtual void VUpdate( const float deltaMs );
        virtual const bool VProcessMessage( const Message& message );
        virtual void VAddSceneNode( GameObjectId id, shared_ptr< SceneNode > pSceneNode );
        virtual void VSetOwner( GameObjectId id ) { IView::VSetOwner( id ); }
        void SetAmbientLightColor( const Color& color ) { m_pScene->SetAmbientLightColor( color ); }
        void SetDiffuseLightColor( const Color& color ) { m_pScene->SetDiffuseLightColor( color ); }
        void SetSpecularLightColor( const Color& color ) { m_pScene->SetSpecularLightColor( color ); }
        void SetLightDirection( const fVec3& dir ) { m_pScene->SetLightDirection( dir ); }

    protected:
        shared_ptr< ScreenElementScene > m_pScene;
        shared_ptr< Renderer > m_pRenderer;
        shared_ptr< CameraNode > m_pCamera;
	    IKeyboardHandler* m_pKeyboardHandler;
        IMouseHandler* m_pMouseHandler;
        MovementController* m_pFreeCameraController;
        float m_currentTime;
        ScreenElementList m_screenElements;
    };
}