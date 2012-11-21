////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Renderer.h"
#include "IRendererImpl.h"
#include "..\Window\IWindowImpl.h"

#ifdef ZN_PLATFORM_WIN32
    #include "D3D11\RendererImplD3D11.h"
#endif

namespace zn
{
    Renderer::Renderer() : m_pRendererImpl( NULL )
    {

    }

    Renderer::~Renderer()
    {
        ZN_SAFE_DELETE( m_pRendererImpl );
    }

    const bool Renderer::Init( const uint8 rendererType, const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl )
    {
        m_rendererType = rendererType;
        if( m_rendererType == RendererType::D3D11 )
        {
#           ifdef ZN_PLATFORM_WIN32
                m_pRendererImpl = ZN_NEW RendererImplD3D11();
                return m_pRendererImpl->VInit( windowSize, isFullscreen, pWindowImpl );
#           endif
        }
        m_rendererType = RendererType::Undefined;
        return false;
    }

    void Renderer::PreRender()
    {
        m_pRendererImpl->VPreRender();
    }

    void Renderer::PostRender()
    {
        m_pRendererImpl->VPostRender();
    }

    void Renderer::Present()
    {
        m_pRendererImpl->VPresent();
    }
    
    bool Renderer::CreateVertexBuffer( VertexBuffer* pVertexBuffer, uint32 byteWidth, const Vertex* pInitData )
    {
        return m_pRendererImpl->VCreateVertexBuffer( pVertexBuffer, byteWidth, pInitData );
    }
    
    bool Renderer::CreateIndexBuffer( IndexBuffer* pIndexBuffer, uint32 byteWidth, const Index* pInitData )
    {
        return m_pRendererImpl->VCreateIndexBuffer( pIndexBuffer, byteWidth, pInitData );
    }

    void Renderer::SetVertexBuffers( VertexBuffer* pVertexBuffer, uint32* pStride, uint32* pOffset )
    {
        m_pRendererImpl->VSetVertexBuffers( pVertexBuffer, pStride, pOffset );
    }
    
    void Renderer::SetIndexBuffer( IndexBuffer* pIndexBuffer )
    {
        m_pRendererImpl->VSetIndexBuffer( pIndexBuffer );
    }
    
    void Renderer::DrawIndexed( uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation )
    {
        m_pRendererImpl->VDrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
    }

    Mat4x4* Renderer::CreateMatrixPerspectiveFovLH( Mat4x4* pOut, float fieldOfView, float aspectRatio, 
        float nearClipDist, float farClipDist )
    {
        return m_pRendererImpl->VCreateMatrixPerspectiveFovLH( pOut, fieldOfView, aspectRatio, nearClipDist, farClipDist );
    }

    Device* Renderer::GetDevice()
    {
        return m_pRendererImpl->VGetDevice();
    }

    DeviceContext* Renderer::GetDeviceContext()
    {
        return m_pRendererImpl->VGetDeviceContext();
    }
}