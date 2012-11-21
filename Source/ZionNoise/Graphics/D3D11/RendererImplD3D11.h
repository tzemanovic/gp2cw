#pragma once
////////////////////////////////////////////////////
// Direct3D 11 renderer
////////////////////////////////////////////////////

#include "..\IRendererImpl.h"
#include "..\Device.h"
#include "..\DeviceContext.h"

namespace zn
{
    class RendererImplD3D11 : public IRendererImpl
    {
    public:
        RendererImplD3D11();
        ~RendererImplD3D11();
        
        // initialize renderer
        bool VInit( const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl );
        // pre-render
        void VPreRender();
        // post-render
        void VPostRender();
        // show rendered image from back buffer
        void VPresent();
        // create the vertex buffer
        bool VCreateVertexBuffer( VertexBuffer* pVertexBuffer, uint32 byteWidth, const Vertex* pInitData );
        // create the index buffer
        bool VCreateIndexBuffer( IndexBuffer* pIndexBuffer, uint32 byteWidth, const Index* pInitData );
        void VSetVertexBuffers( VertexBuffer* pVertexBuffer, uint32* pStride, uint32* pOffset );
        void VSetIndexBuffer( IndexBuffer* pIndexBuffer );
        void VDrawIndexed( uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation );
        
        Mat4x4* VCreateMatrixPerspectiveFovLH( Mat4x4* pOut, float fieldOfView, float aspectRatio, 
            float nearClipDist, float farClipDist );

        Device* VGetDevice() { return m_pDevice; }
        DeviceContext* VGetDeviceContext() { return m_pDeviceContext; }

    private:
        HWND m_hWnd;
        D3D_DRIVER_TYPE m_driverType;
        D3D_FEATURE_LEVEL m_featureLevel;
        
        Device* m_pDevice;
        DeviceContext* m_pDeviceContext;
	    IDXGISwapChain* m_pSwapChain;
	    ID3D11RenderTargetView* m_pRenderTargetView;

	    ID3D11DepthStencilView* m_pDepthStencilView;
	    ID3D11Texture2D* m_pDepthStencilTexture;
    };
}