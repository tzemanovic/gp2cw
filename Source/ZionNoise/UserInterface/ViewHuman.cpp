////////////////////////////////////////////////////
// human view interface
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "ViewHuman.h"
#include "..\Graphics\CameraNode.h"

namespace zn
{
    const unsigned int SCREEN_REFRESH_RATE(1000/60);

    ViewHuman::ViewHuman() : m_nextRender( 0.f )
    {

    }

    ViewHuman::~ViewHuman()
    {

    }

    void ViewHuman::SetRenderer( shared_ptr< Renderer > pRenderer )
    {
        m_pRenderer = pRenderer;
    }

    void ViewHuman::Init()
    {
        if( m_pRenderer )
        {
            m_pScene = shared_ptr< ScreenElementScene >( ZN_NEW ScreenElementScene( m_pRenderer ) );
            m_screenElements.push_front( m_pScene );

            Frustum frustum;
            frustum.Init( ZN_PI / 4.f, 1.f, 1.f, 100.f );
            m_pCamera.reset( ZN_NEW CameraNode( &Mat4x4::identity, frustum ) );
            m_pCamera->Init();
            m_pScene->SetCamera( m_pCamera );
        }
    }

    void ViewHuman::VRender( const float deltaMs )
    {
        m_nextRender -= deltaMs;
        if( m_nextRender <= 0.f )
        {
            g_pGame->GetRenderer()->PreRender();

            m_screenElements.sort( SortBy_SharedPtr_Content< IScreenElement >() );

			for( ScreenElementList::iterator i = m_screenElements.begin(), end = m_screenElements.end(); 
                i != end; ++i )
			{
				if ( ( *i )->IsVisible() )
				{
					( *i )->VRender( deltaMs );
				}
			}

            g_pGame->GetRenderer()->PostRender();
            g_pGame->GetRenderer()->Present();
            m_nextRender = SCREEN_REFRESH_RATE;
        }
    }

    void ViewHuman::VUpdate( const float deltaMs )
    {

    }
    
    const bool ViewHuman::VProcessMessage( const Message& message )
    {
        return false;
    }

    void ViewHuman::VAddSceneNode( shared_ptr< SceneNode > pSceneNode )
    {
        m_pScene->AddSceneNode( pSceneNode );
    }
}