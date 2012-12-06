#pragma once
////////////////////////////////////////////////////
// mesh collider component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "MeshColliderComponent.h"
#include "..\..\GameObject.h"
#include "..\Render\MeshComponent.h"

namespace zn
{
    MeshColliderComponent::MeshColliderComponent()
         : ColliderComponent( GameObjectComponent::MeshCollider ), m_pVerts( NULL ), m_vertCount( 0 )
    {

    }

    MeshColliderComponent::~MeshColliderComponent()
    {
        ZN_SAFE_DELETE_ARRAY( m_pVerts );
    }

    bool MeshColliderComponent::VInit()
    {
        if( !m_pPhysicsShape )
        {
            shared_ptr< MeshComponent > pMeshComponent = MakeStrongPtr( m_pGameObject->GetComponent< MeshComponent >( GameObjectComponent::Mesh ) );
            // check for a mesh component
            if( pMeshComponent )
            {
                for( uint32 j = 0; j < pMeshComponent->GetGeometryCount(); ++j )
                {
                    MeshGeometry* pMeshGeometry = pMeshComponent->GetGeometry( j );
                    m_vertCount += pMeshGeometry->GetVertexCount();
                }

                m_pVerts = ZN_NEW float[3 * m_vertCount];

                uint32 currentVert = 0;
                for( uint32 j = 0; j < pMeshComponent->GetGeometryCount(); ++j )
                {
                    MeshGeometry* pMeshGeometry = pMeshComponent->GetGeometry( j );
                    Vertices vertices = pMeshGeometry->GetVertices();
                    for( Vertices::iterator vi = vertices.begin(); vi != vertices.end(); ++vi )
                    {
                        m_pVerts[currentVert++] = ( *vi ).position.x;
                        m_pVerts[currentVert++] = ( *vi ).position.y;
                        m_pVerts[currentVert++] = ( *vi ).position.z;
                    }
                }

                //Vertices
		        hkStridedVertices stridedVerts;
		        //number of verts
		        stridedVerts.m_numVertices = m_vertCount;
		        //the size of the single vertex
		        stridedVerts.m_striding = 3 * sizeof( float );
		        //The actual vertices
		        stridedVerts.m_vertices = m_pVerts;

		        // Creates a convex vertices shape from vertices.
		        m_pPhysicsShape = new hkpConvexVerticesShape( stridedVerts );
                return true;
            }
        }
        return false;
    }
}