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

    if( initialized )
    {
        shared_ptr< IView > pView = shared_ptr< IView >( ZN_NEW ViewHuman() );
        game.AddView( pView, 0 );

        shared_ptr< GameObject > armoredRecon = shared_ptr< GameObject >( ZN_NEW GameObject( 1 ) );
        shared_ptr< TransformComponent > armoredReconTrans = shared_ptr< TransformComponent >( ZN_NEW TransformComponent() );
        armoredReconTrans->SetPosition( fVec3( 0, 0, 10 ) );
        armoredRecon->AddComponent( armoredRecon, armoredReconTrans );
        shared_ptr< MeshComponent > armoredReconMesh = shared_ptr< MeshComponent >( ZN_NEW MeshComponent() );
        armoredReconMesh->LoadGeometryFromFile( "Assets\\Models\\armoredrecon.fbx" );
        armoredRecon->AddComponent( armoredRecon, armoredReconMesh );
        game.AddGameObject( armoredRecon );

        game.Run();
    }

    return 0;
}