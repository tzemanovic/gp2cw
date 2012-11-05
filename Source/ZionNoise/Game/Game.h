#pragma once
////////////////////////////////////////////////////
// game entry
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "..\Window\WindowStyle.h"
#include "..\Graphics\Renderer.h"

namespace zn
{
    class IView;
    class Window;
    class GameLogic;
    class Timer;

    class Game : INoCopy
    {
    public:
        Game();
        ~Game();
        
        // initialize game
        bool Init( const string& title, const uint16Vec2& windowSize = uint16Vec2( 800, 600 ), const uint8 windowStyle = WindowStyle::Default );
        // run game loop
        void Run();
        // add view
        void AddView( shared_ptr< IView > pView, GameObjectId gameObjectId );

        // accessors
        Renderer* GetRenderer() { return m_pRenderer; }

    private:
        // initalize window
        bool InitWindow( const string& title, const uint16Vec2& windowSize, const uint8 windowStyle );
        // initialize graphics
        bool InitGraphics( const uint16Vec2& windowSize, const uint8 rendererType = RendererType::Default );
        // render
        void Render( const float deltaMs );
        // update
        void Update( const float deltaMs );

        Window* m_pWindow;
        Renderer* m_pRenderer;
        GameLogic* m_pGameLogic;
        Timer* m_pTimer;
    };

    // global pointer to the game
    extern Game* g_pGame;
}