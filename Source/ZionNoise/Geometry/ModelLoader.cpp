////////////////////////////////////////////////////
// model loader
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "ModelLoader.h"
#include "MeshGeometry.h"
#include "..\GameObject\Component\Render\MeshComponent.h"
#include <fbxsdk.h>

namespace zn
{
    void ModelLoader::LoadModelFromFile( MeshComponent& meshComponent, const string& filename )
    {
        string fileExt = filename.substr( filename.find( '.' ) + 1 );
        if( fileExt.compare( "fbx" ) == 0 )
        {
            LoadModelFromFBXFile( meshComponent, filename );
        }
    }
    
    void ModelLoader::CreateCubeGeometry( MeshComponent& meshComponent, const fVec3& dimensions )
    {
        MeshGeometry* pGeometry = ZN_NEW MeshGeometry();

        float halfWidth = dimensions.x / 2.f;
        float halfHeight = dimensions.y / 2.f;
        float halfLength = dimensions.z / 2.f;
        
        Vertex vertices[] =
        {
            { fVec3( -halfWidth,  halfHeight, -halfLength ), Color(), fVec2( 0.0f, 0.0f ), fVec3::up }, // 0 +Y (top face)
            { fVec3(  halfWidth,  halfHeight, -halfLength ), Color(), fVec2( 1.0f, 0.0f ), fVec3::up }, // 1
            { fVec3(  halfWidth,  halfHeight,  halfLength ), Color(), fVec2( 1.0f, 1.0f ), fVec3::up }, // 2
            { fVec3( -halfWidth,  halfHeight,  halfLength ), Color(), fVec2( 0.0f, 1.0f ), fVec3::up }, // 3

            { fVec3( -halfWidth, -halfHeight,  halfLength ), Color(), fVec2( 0.0f, 0.0f ), -1*fVec3::up }, // 4 -Y (bottom face)
            { fVec3(  halfWidth, -halfHeight,  halfLength ), Color(), fVec2( 1.0f, 0.0f ), -1*fVec3::up }, // 5
            { fVec3(  halfWidth, -halfHeight, -halfLength ), Color(), fVec2( 1.0f, 1.0f ), -1*fVec3::up }, // 6
            { fVec3( -halfWidth, -halfHeight, -halfLength ), Color(), fVec2( 0.0f, 1.0f ), -1*fVec3::up }, // 7

            { fVec3(  halfWidth,  halfHeight,  halfLength ), Color(), fVec2( 0.0f, 0.0f ), fVec3::right }, // 8 +X (right face)
            { fVec3(  halfWidth,  halfHeight, -halfLength ), Color(), fVec2( 1.0f, 0.0f ), fVec3::right }, // 9
            { fVec3(  halfWidth, -halfHeight, -halfLength ), Color(), fVec2( 1.0f, 1.0f ), fVec3::right }, // 10
            { fVec3(  halfWidth, -halfHeight,  halfLength ), Color(), fVec2( 0.0f, 1.0f ), fVec3::right }, // 11

            { fVec3( -halfWidth,  halfHeight, -halfLength ), Color(), fVec2( 0.0f, 0.0f ), -1*fVec3::right }, // 12 -X (left face)
            { fVec3( -halfWidth,  halfHeight,  halfLength ), Color(), fVec2( 1.0f, 0.0f ), -1*fVec3::right }, // 13
            { fVec3( -halfWidth, -halfHeight,  halfLength ), Color(), fVec2( 1.0f, 1.0f ), -1*fVec3::right }, // 14
            { fVec3( -halfWidth, -halfHeight, -halfLength ), Color(), fVec2( 0.0f, 1.0f ), -1*fVec3::right }, // 15

            { fVec3( -halfWidth,  halfHeight,  halfLength ), Color(), fVec2( 0.0f, 0.0f ), fVec3::forward }, // 16 +Z (front face)
            { fVec3(  halfWidth,  halfHeight,  halfLength ), Color(), fVec2( 1.0f, 0.0f ), fVec3::forward }, // 17
            { fVec3(  halfWidth, -halfHeight,  halfLength ), Color(), fVec2( 1.0f, 1.0f ), fVec3::forward }, // 18
            { fVec3( -halfWidth, -halfHeight,  halfLength ), Color(), fVec2( 0.0f, 1.0f ), fVec3::forward }, // 19

            { fVec3(  halfWidth,  halfHeight, -halfLength ), Color(), fVec2( 0.0f, 0.0f ), -1*fVec3::forward }, // 20 -Z (back face)
            { fVec3( -halfWidth,  halfHeight, -halfLength ), Color(), fVec2( 1.0f, 0.0f ), -1*fVec3::forward }, // 21
            { fVec3( -halfWidth, -halfHeight, -halfLength ), Color(), fVec2( 1.0f, 1.0f ), -1*fVec3::forward }, // 22
            { fVec3(  halfWidth, -halfHeight, -halfLength ), Color(), fVec2( 0.0f, 1.0f ), -1*fVec3::forward }, // 23
        };
        Index indices[] =
        {
            1, 0, 2, 2, 0, 3, // top face
            5, 4, 6, 6, 4, 7, // bottom
            9, 8, 10, 10, 8, 11, // right
            13, 12, 14, 14, 12, 15, // left
            17, 16, 18, 18, 16, 19, // front
            21, 20, 22, 22, 20, 23 // back
        };
        ComputeTangentsAndBinormals( vertices, 24, indices, 36 );
        for( uint16 i = 0; i < 24; i++ )
        {
            pGeometry->AddVertex( vertices[i] );
        }
        for( uint16 i = 0; i < 36; i++ )
        {
            pGeometry->AddIndex( indices[i] );
        }
        meshComponent.AddGeometry( pGeometry );
    }

    void ModelLoader::LoadModelFromFBXFile( MeshComponent& meshComponent, const string& filename )
    {
        static FbxManager* pManager = FbxManager::Create();
        static FbxIOSettings* pSettings = FbxIOSettings::Create( pManager, IOSROOT );
        pManager->SetIOSettings( pSettings );
        FbxImporter* pImporter = FbxImporter::Create( pManager, "" );
        static FbxGeometryConverter converter( pManager );

        if( !pImporter->Initialize( filename.c_str(), -1, pManager->GetIOSettings() ) )
            return;
        FbxScene* pScene = FbxScene::Create( pManager, "myScene" );
        FbxAxisSystem axisSystem = pScene->GetGlobalSettings().GetAxisSystem();

        pImporter->Import( pScene );
        pImporter->Destroy();

        FbxNode* pRootNode = pScene->GetRootNode();
        FbxMesh* pMesh = NULL;
        if( pRootNode )
        {
            for( int32 i = 0; i < pRootNode->GetChildCount(); ++i )
            {
                FbxNode* pChildNode = pRootNode->GetChild( i );
                for( int32 j = 0; j < pChildNode->GetNodeAttributeCount(); ++j )
                {
                    FbxNodeAttribute* pNodeAttribute = pChildNode->GetNodeAttributeByIndex( j );
                    if( pNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh )
                    {
                        pMesh = ( FbxMesh* )( pNodeAttribute );
                        if( pMesh )
                        {
                            MeshGeometry* pGeometry = ZN_NEW MeshGeometry();
                            pMesh = converter.TriangulateMesh( pMesh );
                            FbxVector4* pFbxVerticies = pMesh->GetControlPoints();
                            uint32 vertexCount = pMesh->GetControlPointsCount();
                            uint32 indexCount = pMesh->GetPolygonVertexCount();
                            Index* pIndicies = ( Index* )pMesh->GetPolygonVertices();
                            Vertex* pVerticies = new Vertex[vertexCount];
                            for( uint32 k = 0; k < vertexCount; ++k )
                            {
                                pVerticies[k].position.x = float( pFbxVerticies[k][0] );
                                pVerticies[k].position.y = float( pFbxVerticies[k][1] );
                                pVerticies[k].position.z = float( pFbxVerticies[k][2] );
                            }

                            for( int32 polyIndex = 0; polyIndex < pMesh->GetPolygonCount(); ++polyIndex )
                            {
                                for( uint32 vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
                                {
                                    uint32 cornerIndex = pMesh->GetPolygonVertex( polyIndex, vertexIndex );
                                    FbxVector4 fbxVertex = pFbxVerticies[cornerIndex];
                                    FbxVector4 fbxNormal;
                                    pMesh->GetPolygonVertexNormal( polyIndex, vertexIndex, fbxNormal );
                                    fbxNormal.Normalize();
                                    pVerticies[cornerIndex].normal = fVec3( float( fbxNormal[0] ), 
                                        float( fbxNormal[1] ), float( fbxNormal[2] ) );
                                    FbxVector2 fbxUV = FbxVector2( 0, 0 );
                                    FbxLayerElementUV* fbxUVs = pMesh->GetLayer( 0 )->GetUVs();
                                    if( fbxUVs )
                                    {
                                        uint32 UVIndex = 0;
                                        switch( fbxUVs->GetMappingMode() ) {
                                        case FbxLayerElement::eByControlPoint:
                                            UVIndex = cornerIndex;
                                            break;
                                        case FbxLayerElement::eByPolygonVertex:
                                            UVIndex = pMesh->GetTextureUVIndex( polyIndex, vertexIndex, FbxLayerElement::eTextureDiffuse );
                                            break;
                                        }
                                        fbxUV = fbxUVs->GetDirectArray().GetAt( UVIndex );
                                        pVerticies[cornerIndex].texCoord.x = float( fbxUV[0] );
									    pVerticies[cornerIndex].texCoord.y = float( 1.0 - fbxUV[1] );
                                    }
                                }
                            }
                            
                            ComputeTangentsAndBinormals( pVerticies, vertexCount, pIndicies, indexCount );
                            for( uint32 k = 0; k < vertexCount; ++k )
                            {
                                pGeometry->AddVertex( pVerticies[k] );
                            }
                            for( uint32 k = 0; k < indexCount; ++k )
                            {
                                pGeometry->AddIndex( pIndicies[k] );
                            }
                            ZN_SAFE_DELETE_ARRAY( pVerticies );
                            meshComponent.AddGeometry( pGeometry );
                        }
                    }
                }
            }
        }
    }

    void ModelLoader::ComputeTangentsAndBinormals( Vertex* pVerticies, uint32 vertexCount, Index* pIndices,
        uint32 indexCount )
    {
        uint32 triCount = indexCount / 3;
	    fVec3* tangents = ZN_NEW fVec3[vertexCount];
	    fVec3* binormals = ZN_NEW fVec3[vertexCount];

	    for( uint32 i = 0; i < triCount; i += 3 )
	    {
		    fVec3 v1 = pVerticies[pIndices[i]].position;
		    fVec3 v2 = pVerticies[pIndices[i+1]].position;
		    fVec3 v3 = pVerticies[pIndices[i+2]].position;

            fVec2 uv1 = pVerticies[pIndices[i]].texCoord;
            fVec2 uv2 = pVerticies[pIndices[i+1]].texCoord;
            fVec2 uv3 = pVerticies[pIndices[i+2]].texCoord;

            fVec3 edge1 = v2 - v1;
            fVec3 edge2 = v3 - v1;
            fVec2 edge1uv = uv2 - uv1;
            fVec2 edge2uv = uv3 - uv1;

            float cp = edge1uv.x * edge2uv.y - edge1uv.y * edge2uv.x;

            if ( cp != 0.0f ) {
                float mul = 1.0f / cp;
                fVec3 tan = (edge1 * edge2uv.y - edge2 * edge1uv.y) * mul;
                fVec3 binorm = (edge1 * edge2uv.x - edge2 * edge1uv.x) * mul;
                tangents[pIndices[i]] += tan;
                binormals[pIndices[i]] += binorm;
                tangents[pIndices[i+1]] += tan;
                binormals[pIndices[i+1]] += binorm;
                tangents[pIndices[i+2]] += tan;
                binormals[pIndices[i+2]] += binorm;
            }
        }
        for( uint32 i = 0; i < vertexCount; ++i )
        {
            fVec3::Normalize( &tangents[i] );
            fVec3::Normalize( &binormals[i] );
            pVerticies[i].tangent = tangents[i];
            pVerticies[i].binormal = binormals[i];
        }
        ZN_SAFE_DELETE_ARRAY( tangents );
        ZN_SAFE_DELETE_ARRAY( binormals );
    }
}