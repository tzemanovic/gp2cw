////////////////////////////////////////////////////
// main function
////////////////////////////////////////////////////

#include "ZNTestGameStd.h"

int main()
{
    Game game;

#   ifdef _DEBUG
    game.Init( "ZN Test Game", iVec2( 800, 600 ), WndStyle::Window );
#   else
    game.Init( "ZN Test Game", iVec2( 800, 600 ), WndStyle::Fullscreen );
#   endif

    game.Run();

    return 0;
}