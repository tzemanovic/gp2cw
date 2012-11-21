#pragma once
////////////////////////////////////////////////////
// Scene implementation
////////////////////////////////////////////////////

#include "SceneNode.h"

namespace zn
{
    class Renderer;
    class CameraNode;

    class Scene
    {
    public:
        Scene( shared_ptr< Renderer > pRenderer );
        virtual ~Scene();

        void AddSceneNode( shared_ptr< SceneNode > pSceneNode );
        void Render( const float deltaMs );
        void Update( const float deltaMs );

        shared_ptr< Renderer > GetRenderer() { return m_pRenderer; }
        shared_ptr< CameraNode > GetCamera() { return m_pCamera; }
        void SetCamera( shared_ptr< CameraNode > pCamera ) { m_pCamera = pCamera; }

    protected:
        shared_ptr< SceneNode > m_pRoot;
        shared_ptr< CameraNode > m_pCamera;
        shared_ptr< Renderer > m_pRenderer;
    };
}