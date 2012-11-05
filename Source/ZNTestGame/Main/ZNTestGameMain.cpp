////////////////////////////////////////////////////
// main function
////////////////////////////////////////////////////

#include "ZNTestGameStd.h"

int main()
{
    Game game;

    bool initialized;
#   ifdef _DEBUG
    initialized = game.Init( "ZN Test Game", uint16Vec2( 800, 600 ), WindowStyle::Window );
#   else
    initialized = game.Init( "ZN Test Game", uint16Vec2( 800, 600 ), WindowStyle::Fullscreen );
#   endif

    shared_ptr< IView > pView = shared_ptr< IView >( ZN_NEW ViewHuman() );
    game.AddView( pView, 0 );

    if( initialized )
        game.Run();

    return 0;
}