////////////////////////////////////////////////////
// mesh component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "MeshComponent.h"
#include "..\..\..\Game\Game.h"
#include "..\..\..\Geometry\ModelLoader.h"
#include "..\TransformComponent.h"
#include "..\GameObjectComponentType.h"
#include "..\..\..\Graphics\SceneNode.h"
#include "..\..\GameObject.h"
#include "..\..\..\Graphics\IMeshMaterial.h"
#include "..\..\..\Geometry\MeshGeometry.h"

namespace zn
{
    MeshComponent::MeshComponent() : RenderComponent( GameObjectComponent::Mesh ), m_pMeshMaterial( NULL )
    {

    }

    MeshComponent::~MeshComponent()
    {
        ZN_SAFE_DELETE( m_pMeshMaterial );
        for( MeshGeometryVector::iterator i = m_meshGeometries.begin(); i != m_meshGeometries.end(); )
        {
            if( *i )
            {
                ZN_SAFE_DELETE( *i );
                i = m_meshGeometries.erase( i );
            }
            else
            {
                ++i;
            }
        }
    }

    bool MeshComponent::VInit()
    {
        if( !m_pMeshMaterial )
        {
            m_pMeshMaterial = IMeshMaterial::CreateDefault( "Assets\\Effects\\Parallax.fx" );
            if( !m_pMeshMaterial )
                return false;
        }
        if( m_pMeshMaterial->VInit() )
        {
            if( RenderComponent::VInit() )
            {
                for( MeshGeometryVector::iterator i = m_meshGeometries.begin(), end = m_meshGeometries.end(); i != end;
                 ++i )
                {
                    if( !( *i )->CreateBuffers() )
                        return false;
                }
                return true;
            }
        }
        return false;
    }

    void MeshComponent::LoadGeometryFromFile( const string& filename )
    {
        ModelLoader::LoadModelFromFile( *this, filename );
    }

    void MeshComponent::CreateCubeGeometry( const fVec3& dimensions )
    {
        ModelLoader::CreateCubeGeometry( *this, dimensions );
    }
    
    void MeshComponent::AddGeometry( MeshGeometry* pMeshGeometry )
    {
        m_meshGeometries.push_back( pMeshGeometry );
    }
    
    MeshGeometry* MeshComponent::GetGeometry( uint32 index )
    {
        if( index > m_meshGeometries.size() )
		    return NULL;
        return m_meshGeometries[index];
    }

    shared_ptr< SceneNode > MeshComponent::VCreateSceneNode()
    {
        shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( m_pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
        // check for a transform component
        if( !pTransformComponent )
        {
            return shared_ptr< SceneNode >();
        }

        shared_ptr< SceneNode > pSceneNode( ZN_NEW SceneNode( m_pGameObject->GetId(), this, RenderPass::GameObjects, &pTransformComponent->GetTransform() ) );
        pSceneNode->SetRadius( VCalculateBoudingSphereRadius() );

        return pSceneNode;
    }

    const float MeshComponent::VCalculateBoudingSphereRadius()
    {
        float radius = 0.0f;
        for( MeshGeometryVector::iterator i = m_meshGeometries.begin(); i != m_meshGeometries.end(); ++i )
        {
            if( *i )
            {
		        Vertices vertices = ( *i )->GetVertices();
                for( Vertices::iterator vi = vertices.begin(); vi != vertices.end(); ++vi )
                {
                    fVec3 extents  = ( *vi ).position;
		            extents.x = abs( extents.x );
		            extents.y = abs( extents.y );
		            extents.z = abs( extents.z );
		            radius = ( radius > extents.x ) ? radius : extents.x;
		            radius = ( radius > extents.y ) ? radius : extents.y;
		            radius = ( radius > extents.z ) ? radius : extents.z;
                }
            }
	    }
	    return radius;
    }
}