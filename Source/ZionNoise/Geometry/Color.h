#pragma once
////////////////////////////////////////////////////
// color
////////////////////////////////////////////////////

#include "..\Graphics\RendererType.h"

namespace zn
{
    class D3DCOLORTYPE;

    template< class T >
    class ColorDef
    {
    public:
        T r, g, b, a;
        
        ColorDef( const T r = 0, const T g = 0, const T b = 0, const T a = 1.0f ) : r( r ), g( g ), b( b ), a( a ) {}
    };

    template<>
    class ColorDef< D3DCOLORTYPE > : public D3DXCOLOR
    {
    public:
        ColorDef( const float r = 0, const float g = 0, const float b = 0, const float a = 1.0f ) : D3DXCOLOR( r, g, b, a ) {}
    };

#ifdef ZN_PLATFORM_WIN32
    typedef ColorDef< D3DCOLORTYPE > Color;
#else
    typedef ColorDef< float > Color;
#endif
}