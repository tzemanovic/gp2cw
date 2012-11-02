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

    bool RendererImplD3D10::Init()
    {

        return false;
    }
}