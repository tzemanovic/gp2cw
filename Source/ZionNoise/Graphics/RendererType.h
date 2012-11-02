#pragma once
////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#ifdef ZN_SYSTEM_WINDOWS
#   include <D3D10.h>
#   include <D3DX10.h>
#endif

namespace zn
{
    namespace RendererType
    {
        enum
        {
            D3D10,
            // default D3D10 on windows
#           if defined(ZN_SYSTEM_WINDOWS)
                Default = D3D10
#           else
                Default
#           endif
        };
    }
}