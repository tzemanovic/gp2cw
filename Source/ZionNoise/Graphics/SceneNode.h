#pragma once
////////////////////////////////////////////////////
// Scene node
////////////////////////////////////////////////////

namespace zn
{
    class RenderComponent;
    class Scene;

    typedef vector< shared_ptr< SceneNode > > SceneNodeVector;

    class SceneNode
    {
    public:
        SceneNode( const GameObjectId gameObjectId, RenderComponent* pRenderComponent, const RenderPassType renderPass,
            const Mat4x4* pToWorld, const Mat4x4* pFromWorld = NULL );
        virtual ~SceneNode();

        void SetParent( SceneNode* pSceneNode );
        void SetTransform( const Mat4x4* pToWorld, const Mat4x4* pFromWorld = NULL );

        virtual void VAddChild( shared_ptr< SceneNode > pSceneNode );
	    virtual bool VIsVisible( Scene *pScene ) const;
        virtual void VPreRender( Scene *pScene );
	    virtual void VRender( Scene *pScene );
	    virtual void VRenderChildren( Scene *pScene );
	    virtual void VPostRender( Scene *pScene );

        void GetTransform( Mat4x4 *pToWorld, Mat4x4 *pFromWorld ) const;
        const fVec3 GetWorldPosition() const;

        const Mat4x4& GetToWorld() const { return m_toWorld; }
	    const Mat4x4& GetFromWorld() const { return m_fromWorld; }
        fVec3 GetPosition() const { return m_toWorld.GetPosition(); }
        const RenderPassType GetRenderPass() const { return m_renderPass; }

    protected:
        GameObjectId m_gameObjectId;
        SceneNodeVector m_children;
        SceneNode* m_pParent;
        RenderComponent* m_pRenderComponent;
        Mat4x4 m_toWorld, m_fromWorld;
        RenderPassType m_renderPass;
        float m_radius;
    };
}