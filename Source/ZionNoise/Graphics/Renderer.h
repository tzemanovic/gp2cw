#pragma once
////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "RendererType.h"
#include "Device.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
// search dr hobbs c++ plugin system
namespace zn
{
    class IRendererImpl;
    class IWindowImpl;

    class Renderer : private INoCopy
    {
    public:
        Renderer();
        ~Renderer();
        
        // initialize renderer
        const bool Init( const uint8 rendererType, const uint16Vec2 windowSize, const bool isFullscreen, 
            IWindowImpl* pWindowImpl );
        // pre-render
        void PreRender();
        // post-render
        void PostRender();
        // show rendered image from back buffer
        void Present();
        // create the vertex buffer
        bool CreateVertexBuffer( VertexBuffer* pVertexBuffer, uint32 byteWidth, const Vertex* pInitData );
        // create the index buffer
        bool CreateIndexBuffer( IndexBuffer* pIndexBuffer, uint32 byteWidth, const Index* pInitData );
        void SetVertexBuffers( VertexBuffer* pVertexBuffer, uint32* pStride, uint32* pOffset );
        void SetIndexBuffer( IndexBuffer* pIndexBuffer );
        void DrawIndexed( uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation );


        Mat4x4* CreateMatrixPerspectiveFovLH( Mat4x4* pOut, float fieldOfView, float aspectRatio, 
            float nearClipDist, float farClipDist );

        Device* GetDevice();
        DeviceContext* GetDeviceContext();

        const uint32 GetRendererType() const { return m_rendererType; }

    private:
        //renderer implementation
        IRendererImpl* m_pRendererImpl;
        uint32 m_rendererType;
    };
}