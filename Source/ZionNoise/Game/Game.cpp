////////////////////////////////////////////////////
// game entry
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Game.h"
#include "..\Window\Window.h"
#include "GameLogic.h"
#include "..\Utilities\Timer.h"

namespace zn
{
    Game* g_pGame = NULL;

    Game::Game() : m_pWindow( NULL ), m_pRenderer( NULL ), m_pGameLogic( NULL ), m_pTimer( NULL )
    {
        g_pGame = this;
    }

    Game::~Game()
    {
        g_pGame = NULL;
        ZN_SAFE_DELETE( m_pTimer );
        ZN_SAFE_DELETE( m_pGameLogic );
        ZN_SAFE_DELETE( m_pRenderer );
        ZN_SAFE_DELETE( m_pWindow );
    }

    bool Game::Init( const string& title, const uint16Vec2& windowSize, const WindowStyleType windowStyle )
    {
        if( !InitWindow( title, windowSize, windowStyle ) )
            return false;
        if( !InitGraphics( windowSize ) )
            return false;
        m_pGameLogic = ZN_NEW GameLogic();
        m_pTimer = ZN_NEW Timer();
        m_pTimer->Start();
        return true;
    }

    void Game::Run()
    {
        // while window is open
        while( m_pWindow->IsOpen() )
        {
            // check for messages
            Message msg;
            while( m_pWindow->PollMessage( msg ) )
            {
                if( msg == Message::Close )
                {
                    m_pWindow->Close();
                }
                // message from keyboard or mouse
                else if( msg == Message::KeyDown || msg == Message::KeyUp ||
                    msg == Message::MouseButtonDown || msg == Message::MouseButtonUp || 
                    msg == Message::MouseMove || msg == Message::MouseWheel )
                {
                    // send message to the views to process
                    for( ViewList::reverse_iterator i = m_pGameLogic->m_viewList.rbegin(), 
                        end = m_pGameLogic->m_viewList.rend(); i != end; ++i )
                    {
                        if( ( *i )->VProcessMessage( msg ) )
                        {
                            break;
                        }
                    }
                }
            }
            // update timer
            float deltaMs = m_pTimer->Update();
            Render( deltaMs );
            Update( deltaMs );
        }
    }

    void Game::AddView( shared_ptr< IView > pView, GameObjectId gameObjectId )
    {
        m_pGameLogic->AddView( pView, gameObjectId );
    }

    bool Game::InitWindow( const string& title, const uint16Vec2& windowSize, const WindowStyleType windowStyle )
    {
        m_pWindow = ZN_NEW Window();
        return m_pWindow->Open( title, windowSize, windowStyle );
    }

    bool Game::InitGraphics( const uint16Vec2& windowSize, const uint8 rendererType )
    {
        if( !m_pWindow )
            return false;
        m_pRenderer = ZN_NEW Renderer();
        return m_pRenderer->Init( rendererType, windowSize, m_pWindow->IsFullscreen(), m_pWindow->GetWindowImpl() );
    }

    void Game::Render( float deltaMs )
    {
        for( ViewList::iterator i = m_pGameLogic->m_viewList.begin(), end = m_pGameLogic->m_viewList.end();
            i != end; ++i )
        {
            ( *i )->VRender( deltaMs );
        }
    }
    
    void Game::Update( float deltaMs )
    {
        for( ViewList::iterator i = m_pGameLogic->m_viewList.begin(), end = m_pGameLogic->m_viewList.end();
            i != end; ++i )
        {
            ( *i )->VUpdate( deltaMs );
        }
    }
}