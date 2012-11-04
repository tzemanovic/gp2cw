////////////////////////////////////////////////////
// main function
////////////////////////////////////////////////////

#include "ZNTestGameStd.h"

int main()
{
    Game game;

#   ifdef _DEBUG
    game.Init( "ZN Test Game", uint16Vec2( 800, 600 ), WindowStyle::Window );
#   else
    game.Init( "ZN Test Game", uint16Vec2( 800, 600 ), WindowStyle::Fullscreen );
#   endif

    game.Run();

    return 0;
}