#pragma once
////////////////////////////////////////////////////
// Scene implementation
////////////////////////////////////////////////////

#include "SceneNode.h"

namespace zn
{
    class Renderer;
    class CameraNode;

    typedef std::map< GameObjectId , shared_ptr< SceneNode > > SceneGameObjectMap;

    class Scene
    {
    public:
        Scene( shared_ptr< Renderer > pRenderer );
        virtual ~Scene();

        void AddSceneNode( GameObjectId id, shared_ptr< SceneNode > pSceneNode );
        void Render( const float deltaMs );
        void Update( const float deltaMs );
        shared_ptr< SceneNode > FindGameObject( GameObjectId id );

        shared_ptr< Renderer > GetRenderer() { return m_pRenderer; }
        shared_ptr< CameraNode > GetCamera() { return m_pCamera; }
        void SetCamera( shared_ptr< CameraNode > pCamera ) { m_pCamera = pCamera; }
        const Color& GetAmbientLightColor() const { return m_abientLightColor; }
        const Color& GetDiffuseLightColor() const { return m_diffuseLightColor; }
        const Color& GetSpecularLightColor() const { return m_specularLightColor; }
        const fVec3& GetLightDirection() const { return m_lightDirection; }
        void SetAmbientLightColor( const Color& color ) { m_abientLightColor = color; }
        void SetDiffuseLightColor( const Color& color ) { m_diffuseLightColor = color; }
        void SetSpecularLightColor( const Color& color ) { m_specularLightColor = color; }
        void SetLightDirection( const fVec3& dir ) { m_lightDirection = dir; }

    protected:
        shared_ptr< SceneNode > m_pRoot;
        shared_ptr< CameraNode > m_pCamera;
        shared_ptr< Renderer > m_pRenderer;
        SceneGameObjectMap m_gameObjectMap;
        Color m_abientLightColor;
        Color m_diffuseLightColor;
        Color m_specularLightColor;
        fVec3 m_lightDirection;
    };
}