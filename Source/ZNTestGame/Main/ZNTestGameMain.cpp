////////////////////////////////////////////////////
// main function
////////////////////////////////////////////////////

#include "ZNTestGameStd.h"
#include "ZNTestGame.h"

int main()
{
    Game game;

    bool initialized;
#   ifdef _DEBUG
    initialized = game.Init( "ZN Test Game", uint16Vec2( 1024, 768 ), WindowStyle::Window );
#   else
    //initialized = game.Init( "ZN Test Game", uint16Vec2( 1024, 768 ), WindowStyle::Fullscreen );
    initialized = game.Init( "ZN Test Game", uint16Vec2( 1024, 768 ), WindowStyle::Window );
#   endif

    if( initialized )
    {
        //shared_ptr< IView > pView = shared_ptr< IView >( ZN_NEW ViewHuman() );
        //game.AddView( pView );

        LuaScriptManager* lua = LuaScriptManager::Get();
        lua->Init();
        lua->GetGameScope()->def( "AddView", ( void( Game::* )( shared_ptr< ViewHumanFirstPerson > ) )&Game::AddView );
        lua->Bind();
        lua_State* pLuaState = lua->GetLuaState();
        module( pLuaState )
	    [
            class_< ViewHumanFirstPerson, ViewHuman, shared_ptr< ViewHumanFirstPerson > >( "ViewHumanFirstPerson" )
                .def( constructor<>() )
                .def( "SetOwner", &ViewHumanFirstPerson::VSetOwner )
                .def( "SetControlledObject", &ViewHumanFirstPerson::SetControlledObject )
        ];


        lua->ExecuteFile( "Assets\\Scripts\\game.lua" );

        try
        {
		    call_function< void >( LuaScriptManager::Get()->GetLuaState(), "initGame" );
	    }
	    catch( luabind::error& )
	    {
		    string error = lua_tostring( LuaScriptManager::Get()->GetLuaState(), -1 );
		    OutputDebugStringA( error.c_str() );
	    }

        /*shared_ptr< GameObject > armoredRecon = shared_ptr< GameObject >( ZN_NEW GameObject( 1 ) );
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

        shared_ptr< GameObject > skySphere = shared_ptr< GameObject >( ZN_NEW GameObject( 7 ) );
        shared_ptr< SkySphereComponent > skySphereMesh = shared_ptr< SkySphereComponent >( 
            ZN_NEW SkySphereComponent( "Assets\\Textures\\SkySphere\\SkyCloudy.dds" ) );
        skySphere->AddComponent( skySphere, skySphereMesh );
        game.AddGameObject( skySphere );*/

        game.Run();
    }

    return 0;
}