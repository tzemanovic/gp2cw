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
        // pre-render
        virtual void VPreRender() = 0;
        // post-render
        virtual void VPostRender() = 0;
        // show rendered image from back buffer
        virtual void VPresent() = 0;
        
    protected:
        // renderer type
        uint8 m_rendererType;
    };
}