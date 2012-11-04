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
        bool Init( const string& title, const uint16Vec2& windowSize = uint16Vec2( 800, 600 ), const uint8 windowStyle = WindowStyle::Default );
        // run game loop
        void Run();

    private:
        // initalize window
        bool InitWindow( const string& title, const uint16Vec2& windowSize, const uint8 windowStyle );
        // initialize graphics
        bool InitGraphics( const uint16Vec2& windowSize, const uint8 rendererType = RendererType::Default );

        Window* m_pWindow;
        Renderer* m_pRenderer;
    };
}