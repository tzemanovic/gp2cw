#pragma once
////////////////////////////////////////////////////
// renderers base
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "RendererType.h"

namespace zn
{
    class IRendererImpl;
    class IWindowImpl;
    class Renderer : private INoCopy
    {
    public:
        Renderer();
        ~Renderer();
        
        // initialize renderer
        const bool Init( const uint8 rendererType, const uint16Vec2 windowSize, const bool isFullscreen, IWindowImpl* pWindowImpl );
        // pre-render
        void PreRender();
        // post-render
        void PostRender();
        // show rendered image from back buffer
        void Present();

    private:
        //renderer implementation
        IRendererImpl* m_pRendererImpl;
    };
}