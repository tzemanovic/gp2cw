#pragma once
////////////////////////////////////////////////////
// game entry
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "..\Window\Window.h"

namespace zn
{
    class Game : INoCopy
    {
    public:
        Game();
        ~Game();
        
        bool Init( const string&, const iVec2& = iVec2( 800, 600 ), const uint8 = WndStyle::Default );
        void Run();

    private:
        bool InitWindow( const string&, const iVec2&, const uint8  );

        Window* m_pWindow;
    };
}