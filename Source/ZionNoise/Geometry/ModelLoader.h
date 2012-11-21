#pragma once
////////////////////////////////////////////////////
// model loader
////////////////////////////////////////////////////

namespace zn
{
    class MeshComponent;

    class ModelLoader
    {
    public:
        static void LoadModelFromFile( MeshComponent* pMeshComponent, const string& filename );

    private:
        static void LoadModelFromFBXFile( MeshComponent* pMeshComponent, const string& filename );
        static void ComputeTangents( Vertex* pVerticies, uint32 vertexCount );
    };
}