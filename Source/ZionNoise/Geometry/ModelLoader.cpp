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
    void ModelLoader::LoadModelFromFile( MeshComponent* pMeshComponent, const string& filename )
    {
        string fileExt = filename.substr( filename.find( '.' ) + 1 );
        if( fileExt.compare( "fbx" ) == 0 )
        {
            LoadModelFromFBXFile( pMeshComponent, filename );
        }
    }

    void ModelLoader::LoadModelFromFBXFile( MeshComponent* pMeshComponent, const string& filename )
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
                            int32* pIndicies = pMesh->GetPolygonVertices();
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

                            ComputeTangents( pVerticies, vertexCount );
                            for( uint32 k = 0; k < vertexCount; ++k )
                            {
                                pGeometry->AddVertex( pVerticies[k] );
                            }
                            for( uint32 k = 0; k < indexCount; ++k )
                            {
                                pGeometry->AddIndex( pIndicies[k] );
                            }
                            ZN_SAFE_DELETE_ARRAY( pVerticies );
                            pMeshComponent->AddGeometry( pGeometry );
                        }
                    }
                }
            }
        }
    }

    void ModelLoader::ComputeTangents( Vertex* pVerticies, uint32 vertexCount )
    {
        uint32 triCount = vertexCount/3;
	    fVec3* tan1 = ZN_NEW fVec3[vertexCount];
	    fVec3* tan2 = ZN_NEW fVec3[vertexCount];

	    for( uint32 i = 0; i < triCount; i += 3 )
	    {
		    fVec3 v1 = pVerticies[i].position;
		    fVec3 v2 = pVerticies[i+1].position;
		    fVec3 v3 = pVerticies[i+2].position;

            fVec2 uv1 = pVerticies[i].texCoord;
            fVec2 uv2 = pVerticies[i+1].texCoord;
            fVec2 uv3 = pVerticies[i+2].texCoord;
			
		    float x1 = v2.x - v1.x;
            float x2 = v3.x - v1.x;
            float y1 = v2.y - v1.y;
            float y2 = v3.y - v1.y;
            float z1 = v2.z - v1.z;
            float z2 = v3.z - v1.z;

            float s1 = uv2.x - uv1.x;
            float s2 = uv3.x - uv1.x;
            float t1 = uv2.y - uv1.y;
            float t2 = uv3.y - uv1.y;

		    float r = 1.0f / ( s1 * t2 - s2 * t1 );
		    fVec3 sdir = fVec3( ( t2 * x1 - t1 * x2 ) * r, ( t2 * y1 - t1 * y2 ) * r, ( t2 * z1 - t1 * z2 ) * r );
            fVec3 tdir = fVec3( ( s1 * x2 - s2 * x1 ) * r, ( s1 * y2 - s2 * y1 ) * r, ( s1 * z2 - s2 * z1 ) * r );

            tan1[i] += sdir;
            tan1[i+1] += sdir;
            tan1[i+2] += sdir;

            tan2[i] += tdir;
            tan2[i+1] += tdir;
            tan2[i+2] += tdir;
	    }
	    for( uint32 i = 0 ; i < vertexCount; i++ )
	    {
		    fVec3 n = pVerticies[i].normal;
		    fVec3 t = tan1[i];
		    fVec3 tmp = ( t - n * fVec3::Vec3Dot( &n , &t ) );
            fVec3::Normalize( &tmp );
		    pVerticies[i].tangent = fVec3( tmp.x, tmp.y, tmp.z );
	    }
        ZN_SAFE_DELETE_ARRAY( tan2 );
        ZN_SAFE_DELETE_ARRAY( tan1 );
    }
}