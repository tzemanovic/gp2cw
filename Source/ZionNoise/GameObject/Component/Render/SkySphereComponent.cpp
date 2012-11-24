////////////////////////////////////////////////////
// sky sphere component
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "SkySphereComponent.h"
#include "..\..\..\Graphics\IMeshMaterial.h"
#include "..\..\..\Graphics\SkySceneNode.h"
#include "..\..\GameObject.h"

namespace zn
{
    SkySphereComponent::SkySphereComponent( const string& textureFilename ) : MeshComponent(), 
        m_textureFilename( textureFilename )
    {

    }

    bool SkySphereComponent::VInit()
    {
        MeshComponent::LoadGeometryFromFile( "Assets\\Models\\Basic\\Sphere.fbx" );
        if( !m_pMeshMaterial )
        {
            m_pMeshMaterial = IMeshMaterial::CreateDefault( "Assets\\Effects\\Sky.fx" );
            if( !m_pMeshMaterial )
                return false;
            if( !m_pMeshMaterial->VLoadEnvMapTexture( m_textureFilename ) )
                return false;
        }
        return MeshComponent::VInit();
    }

    shared_ptr< SceneNode > SkySphereComponent::VCreateSceneNode()
    {
        shared_ptr< SceneNode > pSceneNode( ZN_NEW SkySceneNode( m_pGameObject->GetId(), this ) );
        
        return pSceneNode;
    }
}