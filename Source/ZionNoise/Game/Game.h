#pragma once
////////////////////////////////////////////////////
// game entry
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "..\Window\Window.h"
#include "..\Graphics\Renderer.h"

namespace zn
{
    class Game : INoCopy
    {
    public:
        Game();
        ~Game();
        
        // initialize game
        bool Init( const string&, const iVec2& = iVec2( 800, 600 ), const uint8 = WindowStyle::Default );
        // run game loop
        void Run();

    private:
        // initalize window
        bool InitWindow( const string&, const iVec2&, const uint8 );
        // initialize graphics
        bool InitGraphics( const uint8 = RendererType::Default );

        Window* m_pWindow;
        Renderer* m_pRenderer;
    };
}