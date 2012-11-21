////////////////////////////////////////////////////
// Scene node
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "SceneNode.h"
#include "..\GameObject\GameObject.h"
#include "..\GameObject\Component\TransformComponent.h"
#include "..\GameObject\Component\Render\MeshComponent.h"
#include "Scene.h"
#include "CameraNode.h"
#include "..\Game\GameLogic.h"
#include "..\Graphics\IMeshMaterial.h"

namespace zn
{
    SceneNode::SceneNode( GameObjectId gameObjectId, RenderComponent* pRenderComponent, const Mat4x4* pToWorld, 
        const Mat4x4* pFromWorld ) 
        : m_gameObjectId( gameObjectId ), m_pParent( NULL ), m_pRenderComponent( pRenderComponent ), m_radius( 0.f )
    {
        SetTransform( pToWorld, pFromWorld );
    }

    SceneNode::~SceneNode()
    {

    }

    void SceneNode::SetParent( SceneNode* pSceneNode )
    {
        m_pParent = pSceneNode;
    }
    
    void SceneNode::SetTransform( const Mat4x4* pToWorld, const Mat4x4* pFromWorld )
    {
        m_toWorld = *pToWorld;
        if( !pFromWorld )
            m_fromWorld = m_toWorld.Inverse();
        else
            m_fromWorld = *pFromWorld;
    }

    void SceneNode::VAddChild( shared_ptr< SceneNode> pSceneNode )
    {
        m_children.push_back( pSceneNode );

        pSceneNode->SetParent( this );
    }
    
    bool SceneNode::VIsVisible( Scene *pScene ) const
    {
        Mat4x4 toWorld, fromWorld;
	    pScene->GetCamera()->GetTransform( &toWorld, &fromWorld );

	    fVec3 pos = GetWorldPosition();
	    fVec3 fromWorldPos = fromWorld.Transform( pos );

	    const Frustum& frustum = pScene->GetCamera()->GetFrustum();

	    return frustum.IsInside( fromWorldPos, m_radius );
    }

    void SceneNode::VPreRender( Scene *pScene )
    {
        shared_ptr< GameObject > pGameObject = g_pGame->GetGameLogic()->GetGameObject( m_gameObjectId );
        if( pGameObject )
        {
            shared_ptr< TransformComponent > pTransformComponent = MakeStrongPtr( pGameObject->GetComponent< TransformComponent >( GameObjectComponent::Transform ) );
            if( pTransformComponent )
            {
                m_toWorld = pTransformComponent->GetTransform();
            }
        }
    }

    void SceneNode::VRender( Scene *pScene )
    {
        if( m_pRenderComponent )
        {
            shared_ptr< CameraNode > pCamera = pScene->GetCamera();
            MeshComponent* pMeshComponent = dynamic_cast< MeshComponent* >( m_pRenderComponent );
            if( pMeshComponent )
            {
                IMeshMaterial* pMeshMaterial = pMeshComponent->GetMeshMaterial();
                if( pMeshMaterial )
                {
                    pMeshMaterial->VSetProjection( pCamera->GetProjection() );
                    pMeshMaterial->VSetView( pCamera->GetView() );
                    pMeshMaterial->VSetWorld( m_toWorld );

                    pMeshMaterial->VSetAbientLightColor( Color( 0.5f, 0.5f, 0.5f, 1.0f ) );
                    pMeshMaterial->VSetDiffuseLightColor( Color( 0.5f, 0.5f, 0.5f, 1.0f ) );
			        pMeshMaterial->VSetSpecularLightColor( Color( 0.5f, 0.5f, 0.5f, 1.0f ) );
			        pMeshMaterial->VSetLightDirection( fVec3( 0.f, 0.f, -1.f ) );
			
                    pMeshMaterial->VSetCameraPosition( pCamera->GetWorldPosition() );

                    pMeshMaterial->VSetTextures();
                    pMeshMaterial->VSetMaterials();

                    pMeshMaterial->VBindInputLayout();
                    for( uint32 i = 0; i < pMeshMaterial->VGetPassCount(); ++i )
                    {
                        pMeshMaterial->VApplyPass( i );
                        for( uint32 j = 0; j < pMeshComponent->GetGeometryCount(); ++j )
                        {
                            MeshGeometry* pMeshGeometry = pMeshComponent->GetGeometry( j );
                            pMeshGeometry->SetBuffers();
                            g_pGame->GetRenderer()->DrawIndexed( pMeshGeometry->GetIndexCount(), 0, 0 );
                        }
                    }
                }
            }
        }
    }

	void SceneNode::VRenderChildren( Scene *pScene )
    {
        for( SceneNodeVector::iterator i = m_children.begin(), end = m_children.end(); i != end; ++i )
        {
            if( ( *i )->VIsVisible( pScene ) )
            {
                ( *i )->VPreRender( pScene );
                ( *i )->VRender( pScene );
                ( *i )->VRenderChildren( pScene );
                ( *i )->VPostRender( pScene );
            }
        }
    }

	void SceneNode::VPostRender( Scene *pScene )
    {

    }

    void SceneNode::GetTransform( Mat4x4 *pToWorld, Mat4x4 *pFromWorld ) const
    {
        if( m_toWorld )
            *pToWorld = m_toWorld;
        if( m_fromWorld )
            *pFromWorld = m_fromWorld;
    }

    const fVec3 SceneNode::GetWorldPosition() const
    {
        fVec3 pos = GetPosition();
        if( m_pParent )
        {
            pos += m_pParent->GetWorldPosition();
        }
        return pos;
    }
}