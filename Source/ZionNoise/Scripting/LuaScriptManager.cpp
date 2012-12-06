////////////////////////////////////////////////////
// lua script manager
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "..\Main\ZionNoise.h"

namespace zn
{
    LuaScriptManager::LuaScriptManager() : m_pLuaState( NULL ), gameScope( NULL )
    {

    }

    LuaScriptManager::~LuaScriptManager()
    {
        ZN_SAFE_DELETE( gameScope );
        if( m_pLuaState )
        {
            lua_close( m_pLuaState );
            m_pLuaState = NULL;
        }
    }

    bool LuaScriptManager::Init()
    {
        m_pLuaState = luaL_newstate();
	    luabind::open( m_pLuaState );
        if( !m_pLuaState )
            return false;
        Prebind();

        return true;
    }

    void LuaScriptManager::ExecuteFile( const string& filename )
    {
        luaL_dofile( m_pLuaState, filename.c_str() );
    }

    void LuaScriptManager::Prebind()
    {
        gameScope = ZN_NEW class_< Game >( "Game" );
        gameScope->def( "AddGameObject", &Game::AddGameObject );
        gameScope->def( "AddView", ( void( Game::* )( shared_ptr< IView > ) )&Game::AddView );
        gameScope->def( "AddView", ( void( Game::* )( shared_ptr< ViewHuman > ) )&Game::AddView );
    }

    void LuaScriptManager::Bind()
    {
        /*LuaObject globals = m_pLuaState->GetGlobals();
        globals.RegisterDirect( "ExecuteFile", ( *this ), &LuaScriptManager::ExecuteFile );

        LuaObject fVec3MetaTable = globals.CreateTable( "fVec3MetaTable" );
        fVec3MetaTable.SetObject( "__index", fVec3MetaTable );
        //globals.RegisterObjectDirect( "x", ( fVec3* )0, &fVec3::x );
        //globals.RegisterObjectDirect( "y", ( fVec3* )0, &fVec3::y );
        //globals.RegisterObjectDirect( "z", ( fVec3* )0, &fVec3::z );
        //globals.RegisterObjectDirect( "fVec3", ( fVec3* )0, &fVec3::CreateFromScript );

        LuaObject gameObjectMetaTable = globals.CreateTable( "GameObjectMetaTable" );
        gameObjectMetaTable.SetObject( "__index", gameObjectMetaTable );
        globals.RegisterObjectDirect( "AddComponent", ( GameObject* )0, &GameObject::Destroy );
        */
        module( m_pLuaState )
	    [
            class_< IView, shared_ptr< IView > >( "IView" ),
            class_< ViewHuman, IView, shared_ptr< ViewHuman > >( "ViewHuman" )
                .def( constructor<>() )
                .def( "SetCameraOffset", &ViewHuman::SetCameraOffset )
                .def( "SetAmbientLightColor", &ViewHuman::SetAmbientLightColor )
                .def( "SetDiffuseLightColor", &ViewHuman::SetDiffuseLightColor )
                .def( "SetSpecularLightColor", &ViewHuman::SetSpecularLightColor )
                .def( "SetLightDirection", &ViewHuman::SetLightDirection ),
            class_< fVec2 >( "Vec2" )
                .def( constructor< float, float >() )
                .def_readwrite( "x", &fVec2::x )
                .def_readwrite( "y", &fVec2::y ),
            class_< fVec3 >( "Vec3" )
                .def( constructor< float, float, float >() )
                .def_readwrite( "x", &fVec3::x )
                .def_readwrite( "y", &fVec3::y )
                .def_readwrite( "z", &fVec3::z ),
            class_< fVec4 >( "Vec4" )
                .def( constructor< float, float, float, float >() )
                .def_readwrite( "x", &fVec4::x )
                .def_readwrite( "y", &fVec4::y )
                .def_readwrite( "z", &fVec4::z )
                .def_readwrite( "w", &fVec4::w ),
            class_< Color >( "Color" )
                .def( constructor< float, float, float, float >() )
                .def_readwrite( "r", &Color::r )
                .def_readwrite( "g", &Color::g )
                .def_readwrite( "b", &Color::b )
                .def_readwrite( "a", &Color::a ),
            class_< GameObject, shared_ptr< GameObject > >( "GameObject" )
                .def( constructor< int >() )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< IGameObjectComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< MeshComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< SkySphereComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< TransformComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< RigidBodyComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< BoxColliderComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< MeshColliderComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< FirstPersonCharacterComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< AudioComponent > ) )&GameObject::AddComponent ),
            class_< IGameObjectComponent, shared_ptr< IGameObjectComponent > >( "IGameObjectComponent" ),
            class_< TransformComponent, IGameObjectComponent, shared_ptr< TransformComponent > >( "TransformComponent" )
                .def( constructor<>() )
                .def( "SetPosition", &TransformComponent::SetPosition )
                .def( "SetRotation", ( void( TransformComponent::* )( const fVec3& ) )&TransformComponent::SetRotation )
                .def( "SetScale", &TransformComponent::SetScale ),
            class_< RenderComponent, IGameObjectComponent, shared_ptr< RenderComponent > >( "RenderComponent" ),
            class_< MeshComponent, RenderComponent, shared_ptr< MeshComponent > >( "MeshComponent" )
                .def( constructor<> () )
                .def( "LoadGeometryFromFile", &MeshComponent::LoadGeometryFromFile )
                .def( "CreateCubeGeometry", &MeshComponent::CreateCubeGeometry )
                .def( "GetMeshMaterial", &MeshComponent::GetMeshMaterial ),
            class_< IMeshMaterial >( "IMeshMaterial" )
                .def( "LoadDiffuseTexture", &IMeshMaterial::VLoadDiffuseTexture )
                .def( "LoadSpecularTexture", &IMeshMaterial::VLoadSpecularTexture )
                .def( "LoadBumpTexture", &IMeshMaterial::VLoadBumpTexture )
                .def( "LoadParallaxTexture", &IMeshMaterial::VLoadParallaxTexture )
                .def( "SetTextureRepeat", &IMeshMaterial::VSetTextureRepeat ),
            class_< SkySphereComponent, MeshComponent, shared_ptr< SkySphereComponent > >( "SkySphereComponent" )
                .def( constructor< string >() ),
            class_< LuaScriptManager >( "LuaScriptManager" )
                .scope
			    [
                    def( "GetGame", &LuaScriptManager::GetGame )
                ],
            *gameScope,
            class_< RigidBodyComponent, IGameObjectComponent, shared_ptr< RigidBodyComponent > >( "RigidBodyComponent" )
                .def( constructor< bool, float >() ),
            class_< FirstPersonCharacterComponent, RigidBodyComponent, shared_ptr< FirstPersonCharacterComponent > >( "FirstPersonCharacterComponent" )
                .def( constructor< CharacterControllerInfo >() ),
            class_< CharacterControllerInfo >( "CharacterControllerInfo" )
                .def( constructor<>() ),
            class_< BoxColliderComponent, IGameObjectComponent, shared_ptr< BoxColliderComponent > >( "BoxColliderComponent" )
                .def( constructor< fVec3 >() ),
            class_< MeshColliderComponent, IGameObjectComponent, shared_ptr< MeshColliderComponent > >( "MeshColliderComponent" )
                .def( constructor<>() ),
            class_< AudioManager >( "AudioManager" )
                .scope
			    [
                    def( "Get", &AudioManager::Get )
                ]
                .def( "Init", &AudioManager::Init )
                .def( "LoadSound", &AudioManager::LoadSound )
                .def( "PlaySound", &AudioManager::PlaySound ),
            class_< Sound >( "Sound" )
                .def( constructor<>() ),
            class_< Channel >( "Channel" )
                .def( constructor<>() )
                .def( "Stop", &Channel::Stop ),
            class_< AudioComponent, IGameObjectComponent, shared_ptr< AudioComponent > >( "AudioComponent" )
                .def( constructor<>() )
                .def( "Play", &AudioComponent::Play )
                .def( "SetFilename", &AudioComponent::SetFilename )
        ];
    }
}