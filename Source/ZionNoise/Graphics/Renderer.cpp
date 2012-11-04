////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Renderer.h"
#include "IRendererImpl.h"
#include "..\Window\IWindowImpl.h"

#ifdef ZN_PLATFORM_WIN32
    #include "D3D10\RendererImplD3D10.h"
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
        if( rendererType == RendererType::D3D10 )
        {
#           ifdef ZN_PLATFORM_WIN32
                m_pRendererImpl = ZN_NEW RendererImplD3D10();
                return m_pRendererImpl->VInit( windowSize, isFullscreen, pWindowImpl );
#           else
                return false;
#           endif
        }
        if( rendererType == RendererType::D3D11 )
        {
#           ifdef ZN_PLATFORM_WIN32
                m_pRendererImpl = ZN_NEW RendererImplD3D11();
                return m_pRendererImpl->VInit( windowSize, isFullscreen, pWindowImpl );
#           else
                return false;
#           endif
        }
        return false;
    }
}