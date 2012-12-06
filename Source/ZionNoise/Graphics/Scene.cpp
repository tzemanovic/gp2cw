////////////////////////////////////////////////////
// Scene implementation
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Scene.h"
#include "RootSceneNode.h"

namespace zn
{
    Scene::Scene( shared_ptr< Renderer > pRenderer ) : m_pRenderer( pRenderer ), 
        m_abientLightColor( Color( 0.1f, 0.1f, 0.1f, 0.6f ) ), m_diffuseLightColor( Color( 1.0f, 0.95f, 0.4f, 0.4f ) ), 
        m_specularLightColor( Color( 1.0f, 1.0f, 1.0f, 0.3f ) ), m_lightDirection( fVec3( -0.5f, -1.0f, 0.1f ) )
    {
        // create the root node here
        m_pRoot.reset( ZN_NEW RootSceneNode() );
    }
    
    Scene::~Scene()
    {

    }

    void Scene::AddSceneNode( GameObjectId id, shared_ptr< SceneNode > pSceneNode )
    {
        if( id != NO_GAME_OBJECT_ID )
            m_gameObjectMap[id] = pSceneNode;

        m_pRoot->VAddChild( pSceneNode );
    }
    
    void Scene::Render( const float deltaMs )
    {
        if( m_pRoot && m_pCamera )
        {
            m_pRoot->VRenderChildren( this );
        }
    }

    void Scene::Update( const float deltaMs )
    {
        if( m_pRoot )
            m_pRoot->VUpdate( this, deltaMs );
    }

    shared_ptr< SceneNode > Scene::FindGameObject( GameObjectId id )
    {
        SceneGameObjectMap::iterator i = m_gameObjectMap.find( id );
	    if( i == m_gameObjectMap.end() )
	    {
		    return shared_ptr<SceneNode>();
	    }
	    return i->second;
    }
}