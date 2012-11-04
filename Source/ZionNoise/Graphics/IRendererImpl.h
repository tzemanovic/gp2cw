#pragma once
////////////////////////////////////////////////////
// Direct3D renderers base
////////////////////////////////////////////////////

#include "RendererType.h"
#include "..\Utilities\INoCopy.h"

namespace zn
{
    class IWindowImpl;
    class IRendererImpl : private INoCopy
    {
    public:
        IRendererImpl() {}
        virtual ~IRendererImpl() {}

        // initialize renderer
        virtual bool VInit( const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl ) = 0;
        
    protected:
        // renderer type
        uint8 m_rendererType;
    };
}