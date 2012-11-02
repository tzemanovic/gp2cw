////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Renderer.h"
#include "IRendererImpl.h"
#include "D3D\10\RendererImplD3D10.h"

namespace zn
{
    Renderer::Renderer() : m_pRendererImpl( NULL )
    {

    }

    Renderer::~Renderer()
    {
        ZN_SAFE_DELETE( m_pRendererImpl );
    }

    bool Renderer::Init( const uint8 rendererType )
    {
        if( rendererType == RendererType::D3D10 )
        {
            m_pRendererImpl = ZN_NEW RendererImplD3D10();
            return m_pRendererImpl->Init();
        }
        return false;
    }
}