////////////////////////////////////////////////////
// main function
////////////////////////////////////////////////////

#include "ZNTestGameStd.h"

int main()
{
    Game game;

    bool initialized;
#   ifdef _DEBUG
    initialized = game.Init( "ZN Test Game", uint16Vec2( 1024, 768 ), WindowStyle::Window );
#   else
    initialized = game.Init( "ZN Test Game", uint16Vec2( 1024, 768 ), WindowStyle::Fullscreen );
#   endif

    if( initialized )
    {
        shared_ptr< IView > pView = shared_ptr< IView >( ZN_NEW ViewHuman() );
        game.AddView( pView, 0 );

        shared_ptr< GameObject > armoredRecon = shared_ptr< GameObject >( ZN_NEW GameObject( 1 ) );
        shared_ptr< TransformComponent > armoredReconTrans = shared_ptr< TransformComponent >( ZN_NEW TransformComponent() );
        armoredReconTrans->SetPosition( fVec3( 0, 0, 30 ) );
        armoredRecon->AddComponent( armoredRecon, armoredReconTrans );
        shared_ptr< MeshComponent > armoredReconMesh = shared_ptr< MeshComponent >( ZN_NEW MeshComponent() );
        armoredReconMesh->LoadGeometryFromFile( "Assets\\Models\\Vehicles\\armoredrecon.fbx" );
        armoredRecon->AddComponent( armoredRecon, armoredReconMesh );
        game.AddGameObject( armoredRecon );
        IMeshMaterial* armoredReconMat = armoredReconMesh->GetMeshMaterial();
        armoredReconMat->VLoadDiffuseTexture( "Assets\\Textures\\Vehicles\\armoredrecon_diff.png" );
	    armoredReconMat->VLoadSpecularTexture( "Assets\\Textures\\Vehicles\\armoredrecon_spec.png" );
	    armoredReconMat->VLoadBumpTexture( "Assets\\Textures\\Vehicles\\armoredrecon_N.png" );
	    armoredReconMat->VLoadParallaxTexture( "Assets\\Textures\\Vehicles\\armoredrecon_Height.png" );

        /*shared_ptr< GameObject > armoredRecon1 = shared_ptr< GameObject >( ZN_NEW GameObject( 2 ) );
        shared_ptr< TransformComponent > armoredReconTrans1 = shared_ptr< TransformComponent >( ZN_NEW TransformComponent() );
        armoredReconTrans1->SetPosition( fVec3( 0, 0, -30 ) );
        armoredRecon1->AddComponent( armoredRecon1, armoredReconTrans1 );
        shared_ptr< MeshComponent > armoredReconMesh1 = shared_ptr< MeshComponent >( ZN_NEW MeshComponent() );
        armoredReconMesh1->LoadGeometryFromFile( "Assets\\Models\\Vehicles\\armoredrecon.fbx" );
        armoredRecon1->AddComponent( armoredRecon1, armoredReconMesh1 );
        game.AddGameObject( armoredRecon1 );

        shared_ptr< GameObject > armoredRecon2 = shared_ptr< GameObject >( ZN_NEW GameObject( 3 ) );
        shared_ptr< TransformComponent > armoredReconTrans2 = shared_ptr< TransformComponent >( ZN_NEW TransformComponent() );
        armoredReconTrans2->SetPosition( fVec3( 30, 0, 0) );
        armoredRecon2->AddComponent( armoredRecon2, armoredReconTrans2 );
        shared_ptr< MeshComponent > armoredReconMesh2 = shared_ptr< MeshComponent >( ZN_NEW MeshComponent() );
        armoredReconMesh2->LoadGeometryFromFile( "Assets\\Models\\Vehicles\\armoredrecon.fbx" );
        armoredRecon2->AddComponent( armoredRecon2, armoredReconMesh2 );
        game.AddGameObject( armoredRecon2 );

        shared_ptr< GameObject > armoredRecon3 = shared_ptr< GameObject >( ZN_NEW GameObject( 4 ) );
        shared_ptr< TransformComponent > armoredReconTrans3 = shared_ptr< TransformComponent >( ZN_NEW TransformComponent() );
        armoredReconTrans3->SetPosition( fVec3( -30, 0, 0 ) );
        armoredRecon3->AddComponent( armoredRecon3, armoredReconTrans3 );
        shared_ptr< MeshComponent > armoredReconMesh3 = shared_ptr< MeshComponent >( ZN_NEW MeshComponent() );
        armoredReconMesh3->LoadGeometryFromFile( "Assets\\Models\\Vehicles\\armoredrecon.fbx" );
        armoredRecon3->AddComponent( armoredRecon3, armoredReconMesh3 );
        game.AddGameObject( armoredRecon3 );

        shared_ptr< GameObject > armoredRecon4 = shared_ptr< GameObject >( ZN_NEW GameObject( 5 ) );
        shared_ptr< TransformComponent > armoredReconTrans4 = shared_ptr< TransformComponent >( ZN_NEW TransformComponent() );
        armoredReconTrans4->SetPosition( fVec3( 0, 30, 0 ) );
        armoredRecon4->AddComponent( armoredRecon4, armoredReconTrans4 );
        shared_ptr< MeshComponent > armoredReconMesh4 = shared_ptr< MeshComponent >( ZN_NEW MeshComponent() );
        armoredReconMesh4->LoadGeometryFromFile( "Assets\\Models\\Vehicles\\armoredrecon.fbx" );
        armoredRecon4->AddComponent( armoredRecon4, armoredReconMesh4 );
        game.AddGameObject( armoredRecon4 );

        shared_ptr< GameObject > armoredRecon5 = shared_ptr< GameObject >( ZN_NEW GameObject( 6 ) );
        shared_ptr< TransformComponent > armoredReconTrans5 = shared_ptr< TransformComponent >( ZN_NEW TransformComponent() );
        armoredReconTrans5->SetPosition( fVec3( 0, -30, 0 ) );
        armoredRecon5->AddComponent( armoredRecon5, armoredReconTrans5 );
        shared_ptr< MeshComponent > armoredReconMesh5 = shared_ptr< MeshComponent >( ZN_NEW MeshComponent() );
        armoredReconMesh5->LoadGeometryFromFile( "Assets\\Models\\Vehicles\\armoredrecon.fbx" );
        armoredRecon5->AddComponent( armoredRecon5, armoredReconMesh5 );
        game.AddGameObject( armoredRecon5 );*/

        shared_ptr< GameObject > skySphere = shared_ptr< GameObject >( ZN_NEW GameObject( 7 ) );
        shared_ptr< SkySphereComponent > skySphereMesh = shared_ptr< SkySphereComponent >( 
            ZN_NEW SkySphereComponent( "Assets\\Textures\\SkySphere\\SkyCloudy.dds" ) );
        skySphere->AddComponent( skySphere, skySphereMesh );
        game.AddGameObject( skySphere );

        game.Run();
    }

    return 0;
}