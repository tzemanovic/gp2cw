#pragma once
////////////////////////////////////////////////////
// Direct3D renderers base
////////////////////////////////////////////////////

#include "RendererType.h"
#include "..\Utilities\INoCopy.h"

namespace zn
{
    class IWindowImpl;
    class IRendererImpl : private INoCopy
    {
    public:
        IRendererImpl() {}
        virtual ~IRendererImpl() {}

        // initialize renderer
        virtual bool VInit( const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl ) = 0;
        // pre-render
        virtual void VPreRender() = 0;
        // post-render
        virtual void VPostRender() = 0;
        // show rendered image from back buffer
        virtual void VPresent() = 0;
        // create the vertex buffer
        virtual bool VCreateVertexBuffer( VertexBuffer* pVertexBuffer, uint32 byteWidth, const Vertex* pInitData ) = 0;
        // create the index buffer
        virtual bool VCreateIndexBuffer( IndexBuffer* pIndexBuffer, uint32 byteWidth, const Index* pInitData ) = 0;
        virtual void VSetVertexBuffers( VertexBuffer* pVertexBuffer, uint32* pStride, uint32* pOffset ) = 0;
        virtual void VSetIndexBuffer( IndexBuffer* pIndexBuffer ) = 0;
        virtual void VDrawIndexed( uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation ) = 0;

        virtual Mat4x4* VCreateMatrixPerspectiveFovLH( Mat4x4* pOut, float fieldOfView, float aspectRatio, 
            float nearClipDist, float farClipDist ) = 0;
        
        virtual Device* VGetDevice() = 0;
        virtual DeviceContext* VGetDeviceContext() = 0;
        
    protected:
        // renderer type
        uint8 m_rendererType;
    };
}