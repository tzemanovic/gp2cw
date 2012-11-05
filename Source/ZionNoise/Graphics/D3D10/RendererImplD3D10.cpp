////////////////////////////////////////////////////
// Direct3D 10 renderer
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "RendererImplD3D10.h"

namespace zn
{
    RendererImplD3D10::RendererImplD3D10()
    {
        m_rendererType = RendererType::D3D10;
    }

    RendererImplD3D10::~RendererImplD3D10()
    {

    }

    bool RendererImplD3D10::VInit( const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl )
    {
        // not implemented yet
        return false;
    }

    void RendererImplD3D10::VPreRender()
    {

    }

    void RendererImplD3D10::VPostRender()
    {

    }

    void RendererImplD3D10::VPresent()
    {

    }
}