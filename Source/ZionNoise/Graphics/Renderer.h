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
    class Renderer
    {
    public:
        enum Type
        {
            DirectX10,
#           if defined(ZN_SYSTEM_WINDOWS)
                Default = DirectX10
#           else
                Default
#           endif
        };

        Renderer() : type( Type::Default ) {}
        Renderer( const Renderer::Type type ) : type( type ) {}

        Type type;
    };
}