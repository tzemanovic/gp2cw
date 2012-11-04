#pragma once
////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#ifdef ZN_PLATFORM_WIN32
#   include <D3D11.h>
#   include <D3DX11.h>
#   include <D3D10.h>
#   include <D3DX10.h>
#   include <DxErr.h>
#endif

namespace zn
{
    namespace RendererType
    {
        enum
        {
            D3D10,
            D3D11,
            // default D3D10 on windows
#           if defined(ZN_PLATFORM_WIN32)
                Default = D3D11
#           else
                Default
#           endif
        };
    }
}