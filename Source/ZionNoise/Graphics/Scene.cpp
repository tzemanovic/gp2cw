////////////////////////////////////////////////////
// Scene implementation
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Scene.h"
#include "RootSceneNode.h"

namespace zn
{
    Scene::Scene( shared_ptr< Renderer > pRenderer ) : m_pRenderer( pRenderer )
    {
        // create the root node here
        m_pRoot.reset( ZN_NEW RootSceneNode() );
    }
    
    Scene::~Scene()
    {

    }

    void Scene::AddSceneNode( shared_ptr< SceneNode > pSceneNode )
    {
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

    }
}