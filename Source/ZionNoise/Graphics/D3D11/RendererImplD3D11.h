#pragma once
////////////////////////////////////////////////////
// Direct3D 11 renderer
////////////////////////////////////////////////////

#include "..\IRendererImpl.h"

namespace zn
{
    class RendererImplD3D11 : public IRendererImpl
    {
    public:
        RendererImplD3D11();
        ~RendererImplD3D11();
        
        // initialize renderer
        virtual bool VInit( const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl );

    private:
        HWND m_hWnd;
        D3D_DRIVER_TYPE m_driverType;
        D3D_FEATURE_LEVEL m_featureLevel;
        
        ID3D11Device* m_pDevice;
        ID3D11DeviceContext* m_pDeviceContext;
	    IDXGISwapChain* m_pSwapChain;
	    ID3D11RenderTargetView* m_pRenderTargetView;

	    ID3D11DepthStencilView* m_pDepthStencilView;
	    ID3D11Texture2D* m_pDepthStencilTexture;
    };
}