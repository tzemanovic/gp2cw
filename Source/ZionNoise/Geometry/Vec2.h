#pragma once
////////////////////////////////////////////////////
// 2d vector
////////////////////////////////////////////////////

#include "..\Graphics\RendererType.h"

namespace zn
{
    class D3DVECTOR2TYPE;

    template< class T >
    class Vec2
    {
    public:
        T x, y;
        
        Vec2( const T x = 0, const T y = 0 ) : x( x ), y( y ) {}
    };
    
    template<>
    class Vec2< D3DVECTOR2TYPE > : public D3DXVECTOR2
    {
    public:
        Vec2( const float x = 0, const float y = 0 ) : D3DXVECTOR2( x, y ) {}
    };
    
    typedef Vec2< uint16 > uint16Vec2;
    typedef Vec2< int16 > int16Vec2;
    typedef Vec2< uint32 > uint32Vec2;
    typedef Vec2< int32 > int32Vec2;

#ifdef ZN_PLATFORM_WIN32
    typedef Vec2< D3DVECTOR2TYPE > fVec2;
#else
    typedef Vec2< float > fVec2;
#endif
}