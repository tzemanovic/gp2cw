////////////////////////////////////////////////////
// game entry
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Game.h"

namespace zn
{
    Game::Game() : m_pWindow( NULL ), m_pRenderer( NULL )
    {
        
    }

    Game::~Game()
    {
        ZN_SAFE_DELETE( m_pRenderer );
        ZN_SAFE_DELETE( m_pWindow );
    }

    bool Game::Init( const string& title, const uint16Vec2& windowSize, const uint8 windowStyle )
    {
        if( !InitWindow( title, windowSize, windowStyle ) )
            return false;
        if( !InitGraphics( windowSize ) )
            return false;
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
                    m_pWindow->Close();
            }
        }
    }

    bool Game::InitWindow( const string& title, const uint16Vec2& windowSize, const uint8 windowStyle )
    {
        m_pWindow = ZN_NEW Window();
        return m_pWindow->Open( title, windowSize, windowStyle );
    }

    bool Game::InitGraphics( const uint16Vec2& windowSize, const uint8 rendererType )
    {
        if( !m_pWindow )
            return false;
        m_pRenderer = ZN_NEW Renderer();
        return m_pRenderer->Init( rendererType, windowSize, true, m_pWindow->GetWindowImpl() );
    }
}