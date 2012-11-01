////////////////////////////////////////////////////
// game entry
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Game.h"

namespace zn
{
    Game::Game() : m_pWindow( NULL )
    {
        
    }

    Game::~Game()
    {
        ZN_SAFE_DELETE( m_pWindow );
    }

    bool Game::Init( const string& title, const iVec2& windowSize, const uint8 windowStyle )
    {
        if( !InitWindow( title, windowSize, windowStyle ) )
            return false;
        return true;
    }

    void Game::Run()
    {
        while( m_pWindow->IsOpen() )
        {
            Message msg;
            while( m_pWindow->PollMessage( msg ) )
            {
                if( msg == Message::Close )
                    m_pWindow->Close();
            }
        }
    }

    bool Game::InitWindow( const string& title, const iVec2& windowSize, const uint8 windowStyle )
    {
        m_pWindow = ZN_NEW Window();
        if( !m_pWindow->Open( title, windowSize, windowStyle ) )
            return false;
        return true;
    }
}