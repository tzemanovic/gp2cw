////////////////////////////////////////////////////
// mesh geometry
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "MeshGeometry.h"

namespace zn
{
    MeshGeometry::MeshGeometry() : m_pVertexBuffer( NULL ), m_pIndexBuffer( NULL )
    {

    }

    MeshGeometry::~MeshGeometry()
    {
        ZN_SAFE_DELETE( m_pIndexBuffer );
        ZN_SAFE_DELETE( m_pVertexBuffer );
    }

    void MeshGeometry::AddVertex( const Vertex vertex )
    {
        m_vertices.push_back( vertex );
    }
    
    void MeshGeometry::AddIndex( const Index index )
    {
        m_indicies.push_back( index );
    }

    bool MeshGeometry::CreateBuffers()
    {
        m_pVertexBuffer = ZN_NEW VertexBuffer();
        m_pIndexBuffer = ZN_NEW IndexBuffer();
        shared_ptr< Renderer > pRenderer = g_pGame->GetRenderer();
        if( pRenderer->CreateVertexBuffer( m_pVertexBuffer, sizeof( Vertex ) * m_vertices.size(), &m_vertices.at( 0 ) ) )
            if( pRenderer->CreateIndexBuffer( m_pIndexBuffer, sizeof( Index ) * m_indicies.size(), &m_indicies.at( 0 ) ) )
                return true;
        return false;
    }

    void MeshGeometry::SetBuffers()
    {
        uint32 stride = sizeof( Vertex );
        uint32 offset = 0;
        shared_ptr< Renderer > pRenderer = g_pGame->GetRenderer();
        pRenderer->SetVertexBuffers( m_pVertexBuffer, &stride, &offset );
        pRenderer->SetIndexBuffer( m_pIndexBuffer );
    }
}