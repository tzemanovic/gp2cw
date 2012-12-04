////////////////////////////////////////////////////
// lua script manager
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "LuaScriptManager.h"
#include "..\GameObject\GameObject.h"
#include "..\GameObject\Component\IGameObjectComponent.h"
#include "..\GameObject\Component\TransformComponent.h"
#include "..\GameObject\Component\Render\MeshComponent.h"
#include "..\GameObject\Component\Render\SkySphereComponent.h"
#include "..\Graphics\IMeshMaterial.h"
#include "..\GameObject\Component\Physics\RigidBodyComponent.h"
#include "..\GameObject\Component\Physics\BoxColliderComponent.h"

namespace zn
{
    LuaScriptManager::LuaScriptManager() : m_pLuaState( NULL )
    {

    }

    LuaScriptManager::~LuaScriptManager()
    {
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

        Bind();
        return true;
    }

    void LuaScriptManager::ExecuteFile( const string& filename )
    {
        luaL_dofile( m_pLuaState, filename.c_str() );
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
            class_< fVec3 >( "fVec3" )
                .def( constructor< float, float, float >() )
                .def_readwrite( "x", &fVec3::x )
                .def_readwrite( "y", &fVec3::y )
                .def_readwrite( "z", &fVec3::z ),
            class_< GameObject, shared_ptr< GameObject > >( "GameObject" )
                .def( constructor< int >() )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< IGameObjectComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< MeshComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< SkySphereComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< TransformComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< RigidBodyComponent > ) )&GameObject::AddComponent )
                .def( "AddComponent", ( void( GameObject::* )( shared_ptr< GameObject >, shared_ptr< BoxColliderComponent > ) )&GameObject::AddComponent ),
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
                .def( "VLoadDiffuseTexture", &IMeshMaterial::VLoadDiffuseTexture )
                .def( "VLoadSpecularTexture", &IMeshMaterial::VLoadSpecularTexture )
                .def( "VLoadBumpTexture", &IMeshMaterial::VLoadBumpTexture )
                .def( "VLoadParallaxTexture", &IMeshMaterial::VLoadParallaxTexture ),
            class_< SkySphereComponent, MeshComponent, shared_ptr< SkySphereComponent > >( "SkySphereComponent" )
                .def( constructor< string >() ),
            class_< LuaScriptManager >( "LuaScriptManager" )
                .scope
			    [
                    def( "GetGame", &LuaScriptManager::GetGame )
                ],
            class_< Game >( "Game" )
                .def( "AddGameObject", &Game::AddGameObject ),
            class_< RigidBodyComponent, IGameObjectComponent, shared_ptr< RigidBodyComponent > >( "RigidBodyComponent" )
                .def( constructor< bool, float >() ),
            class_< BoxColliderComponent, IGameObjectComponent, shared_ptr< BoxColliderComponent > >( "BoxColliderComponent" )
                .def( constructor< fVec3 >() )
        ];
    }
}