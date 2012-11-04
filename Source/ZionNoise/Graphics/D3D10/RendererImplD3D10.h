#pragma once
////////////////////////////////////////////////////
// Direct3D 10 renderer
////////////////////////////////////////////////////

#include "..\IRendererImpl.h"

namespace zn
{
    class RendererImplD3D10 : public IRendererImpl
    {
    public:
        RendererImplD3D10();
        ~RendererImplD3D10();
        
        // initialize renderer
        virtual bool VInit( const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl );

    private:
        ID3D10Device* m_pD3DDevice;
	    IDXGISwapChain* m_pSwapChain;
	    ID3D10RenderTargetView* m_pRenderTargetView;
	    ID3D10DepthStencilView* m_pDepthStencilView;
	    ID3D10Texture2D* m_pDepthStencilTexture;
    };
}