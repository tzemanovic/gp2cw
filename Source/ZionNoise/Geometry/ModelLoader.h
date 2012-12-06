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
        static void LoadModelFromFile( MeshComponent& meshComponent, const string& filename, const float scale );
        static void CreateCubeGeometry( MeshComponent& meshComponent, const fVec3& dimensions );

    private:
        static void LoadModelFromFBXFile( MeshComponent& meshComponent, const string& filename, const float scale );
        static void ComputeTangentsAndBinormals( Vertex* pVerticies, uint32 vertexCount, Index* pIndices,
            uint32 indexCount );
    };
}