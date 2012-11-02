#pragma once
////////////////////////////////////////////////////
// Direct3D renderers base
////////////////////////////////////////////////////

#include "RendererType.h"

namespace zn
{
    class IRendererImpl
    {
    public:
        IRendererImpl() {}
        virtual ~IRendererImpl() {}

        // initialize renderer
        virtual bool Init() = 0;
        
    protected:
        // renderer type
        uint8 m_rendererType;
    };
}