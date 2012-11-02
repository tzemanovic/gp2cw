#pragma once
////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "RendererType.h"

namespace zn
{
    class IRendererImpl;
    class Renderer : private INoCopy
    {
    public:
        Renderer();
        ~Renderer();
        
        // initialize renderer
        bool Init( const uint8 );
    private:
        //renderer implementation
        IRendererImpl* m_pRendererImpl;
    };
}