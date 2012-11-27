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
        static void LoadModelFromFile( MeshComponent& meshComponent, const string& filename );
        static void CreateCubeGeometry( MeshComponent& meshComponent, const fVec3& dimensions );

    private:
        static void LoadModelFromFBXFile( MeshComponent& meshComponent, const string& filename );
        static void ComputeTangents( Vertex* pVerticies, uint32 vertexCount );
    };
}