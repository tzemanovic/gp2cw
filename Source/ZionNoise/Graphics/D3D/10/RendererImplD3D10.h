#pragma once
////////////////////////////////////////////////////
// Direct3D 10 renderer
////////////////////////////////////////////////////

#include "..\..\IRendererImpl.h"

namespace zn
{
    class RendererImplD3D10 : public IRendererImpl
    {
    public:
        RendererImplD3D10();
        ~RendererImplD3D10();
        
        // initialize renderer
        virtual bool Init();
    };
}