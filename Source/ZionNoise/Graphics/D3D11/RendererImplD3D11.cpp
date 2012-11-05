////////////////////////////////////////////////////
// Direct3D 11 renderer
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "RendererImplD3D11.h"
#include "..\..\Window\Win32\WindowImplWin32.h"

namespace zn
{
    RendererImplD3D11::RendererImplD3D11() : m_hWnd( NULL ), m_driverType( D3D_DRIVER_TYPE_NULL ), 
        m_featureLevel( D3D_FEATURE_LEVEL_11_0 ), m_pDevice( NULL ), m_pDeviceContext( NULL ), m_pSwapChain( NULL ), 
        m_pRenderTargetView( NULL ), m_pDepthStencilView( NULL ), m_pDepthStencilTexture( NULL )
    {
        m_rendererType = RendererType::D3D11;
    }

    RendererImplD3D11::~RendererImplD3D11()
    {
        m_pSwapChain->SetFullscreenState( false, NULL );
        ZN_SAFE_RELEASE( m_pDepthStencilTexture );
        ZN_SAFE_RELEASE( m_pDepthStencilView );
        ZN_SAFE_RELEASE( m_pRenderTargetView );
        ZN_SAFE_RELEASE( m_pSwapChain );
        ZN_SAFE_RELEASE( m_pDeviceContext );
        ZN_SAFE_RELEASE( m_pDevice );
    }

    bool RendererImplD3D11::VInit( const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl )
    {
        // get window implementation
        WindowImplWin32* pWindowImplWin32 = dynamic_cast<WindowImplWin32*>(pWindowImpl);
        if( !pWindowImplWin32 )
            return false;
        // get window handle
        m_hWnd = pWindowImplWin32->GetWndHandle();
        
        // driver types for fallback
        D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE };
        uint8 totalDriverTypes = ARRAYSIZE( driverTypes );

        // fallback feature levels
        D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
        uint8 totalFeatureLevels = ARRAYSIZE( featureLevels );

        // swap chain description
        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) );
        swapChainDesc.BufferCount = isFullscreen ? 2 : 1;
        swapChainDesc.BufferDesc.Width = windowSize.x;
        swapChainDesc.BufferDesc.Height = windowSize.y;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = m_hWnd;
        swapChainDesc.Windowed = !isFullscreen;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        // device creation flags
        uint32 creationFlags = 0;
#       ifdef _DEBUG
            creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#       endif

        HRESULT result;
        uint8 driver = 0;
        // loop through driver types and attempt to create device
        for( driver; driver < totalDriverTypes; ++driver )
        {
            result = D3D11CreateDeviceAndSwapChain( 0, driverTypes[driver], 0, creationFlags, featureLevels, 
                totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, &m_featureLevel,
                &m_pDeviceContext );
            if( SUCCEEDED( result ) )
            {
                m_driverType = driverTypes[driver];
                break;
            }
        }
        /*result = D3D11CreateDeviceAndSwapChain( 0, D3D_DRIVER_TYPE_HARDWARE, 0, NULL, NULL, 
                NULL, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, &m_featureLevel,
                &m_pDeviceContext );*/
        if( FAILED( result ) )
        {
            DXTRACE_MSG( L"Failed to create the Direct3D device!" );
            return false;
        }

        // back buffer texture to link render target with back buffer
        ID3D11Texture2D* pBackBufferTexture;
        if( FAILED( m_pSwapChain->GetBuffer( 0, _uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBufferTexture ) ) )
        {
            DXTRACE_MSG( L"Failed to get the swap chain back buffer!" );
            return false;
        }
        
        D3D11_TEXTURE2D_DESC depthDesc;
        depthDesc.Width = windowSize.x;
        depthDesc.Height = windowSize.y;
        depthDesc.MipLevels = 1;
        depthDesc.ArraySize = 1;
        depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	    depthDesc.SampleDesc.Count=1;
	    depthDesc.SampleDesc.Quality=0;
	    depthDesc.Usage = D3D11_USAGE_DEFAULT;
	    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	    depthDesc.CPUAccessFlags = 0;
	    depthDesc.MiscFlags = 0;

        if( FAILED( m_pDevice->CreateTexture2D( &depthDesc, NULL, &m_pDepthStencilTexture ) ) )
        {
            DXTRACE_MSG( L"Failed to create depth stencil texture!" );
            return false;
        }

        D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
        depthViewDesc.Format = depthDesc.Format;
	    depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	    depthViewDesc.Texture2D.MipSlice = 0;
        depthViewDesc.Flags = 0;

        if( FAILED( m_pDevice->CreateDepthStencilView( m_pDepthStencilTexture, &depthViewDesc, &m_pDepthStencilView ) ) )
        {
            DXTRACE_MSG( L"Failed to create depth stencil view!" );
            return false;
        }

        if( FAILED( m_pDevice->CreateRenderTargetView( pBackBufferTexture, NULL, &m_pRenderTargetView ) ) )
        {
            DXTRACE_MSG( L"Failed to create render target view!" );
            ZN_SAFE_RELEASE( pBackBufferTexture );
            return false;
        }
        ZN_SAFE_RELEASE( pBackBufferTexture );
        
        m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );

        // setup the viewport
        D3D11_VIEWPORT viewport;
        viewport.Width = windowSize.x;
        viewport.Height = windowSize.y;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0.f;
        viewport.TopLeftY = 0.f;

        m_pDeviceContext->RSSetViewports( 1, &viewport );
        
        return true;
    }

    void RendererImplD3D11::VPreRender()
    {
        // clear the render target and depth stencil
        // can be commented out once we render skybox
        float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 
        m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
	    m_pDeviceContext->ClearDepthStencilView( m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
    }

    void RendererImplD3D11::VPostRender()
    {

    }

    void RendererImplD3D11::VPresent()
    {
        // flip the swap chain
        m_pSwapChain->Present( 0, 0 );
    }
}