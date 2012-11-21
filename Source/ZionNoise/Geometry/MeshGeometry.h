#pragma once
////////////////////////////////////////////////////
// mesh geometry
////////////////////////////////////////////////////

#include "..\Graphics\VertexBuffer.h"
#include "..\Graphics\IndexBuffer.h"

namespace zn
{
    typedef vector< Vertex > Verticies;
    typedef vector< Index > Indicies;

    class MeshGeometry
    {
    public:
        MeshGeometry();
        ~MeshGeometry();

        void AddVertex( const Vertex vertex );
        void AddIndex( const Index index );
        bool CreateBuffers();
        void SetBuffers();

        uint32 GetIndexCount() { return m_indicies.size(); }

    private:
        Verticies m_vertices;
        Indicies m_indicies;
        VertexBuffer* m_pVertexBuffer;
        IndexBuffer* m_pIndexBuffer;
    };
}