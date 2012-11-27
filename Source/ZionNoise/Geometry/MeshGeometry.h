#pragma once
////////////////////////////////////////////////////
// mesh geometry
////////////////////////////////////////////////////

#include "..\Graphics\VertexBuffer.h"
#include "..\Graphics\IndexBuffer.h"

namespace zn
{
    typedef vector< Vertex > Vertices;
    typedef vector< Index > Indices;

    class MeshGeometry
    {
    public:
        MeshGeometry();
        ~MeshGeometry();

        void AddVertex( const Vertex vertex );
        void AddIndex( const Index index );
        bool CreateBuffers();
        void SetBuffers();

        uint32 GetIndexCount() { return m_indices.size(); }
        Vertices& GetVertices() { return m_vertices; }

    private:
        Vertices m_vertices;
        Indices m_indices;
        VertexBuffer* m_pVertexBuffer;
        IndexBuffer* m_pIndexBuffer;
    };
}