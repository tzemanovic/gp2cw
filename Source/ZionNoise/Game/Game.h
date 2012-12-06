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
    class SceneNode;
    class GameObject;

    class Game : INoCopy
    {
    public:
        Game();
        ~Game();
        
        // initialize game
        bool Init( const string& title, const uint16Vec2& windowSize = uint16Vec2( 800, 600 ), const WindowStyleType windowStyle = WindowStyle::Default );
        // run game loop
        void Run();
        // add view
        void AddView( shared_ptr< IView > pView );
        void AddSceneNode( GameObjectId id, shared_ptr< SceneNode > pSceneNode );
        const uint16Vec2& GetWindowSize() const;
        void AddGameObject( shared_ptr< GameObject > pGameObject );

        // accessors
        shared_ptr< Renderer > GetRenderer() { return m_pRenderer; }
        const uint32 GetRendererType() { return m_pRenderer->GetRendererType(); }
        GameLogic* GetGameLogic() { return m_pGameLogic; }
        Window* GetWindow() { return m_pWindow; }

    private:
        // initalize window
        bool InitWindow( const string& title, const uint16Vec2& windowSize, const WindowStyleType windowStyle );
        // initialize graphics
        bool InitGraphics( const uint16Vec2& windowSize, const uint8 rendererType = RendererType::Default );
        // render
        void Render( const float deltaMs );
        // update
        void Update( const float deltaMs );

        Window* m_pWindow;
        shared_ptr< Renderer > m_pRenderer;
        GameLogic* m_pGameLogic;
        Timer* m_pTimer;
    };

    // global pointer to the game
    extern Game* g_pGame;
}