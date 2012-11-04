#pragma once
////////////////////////////////////////////////////
// 2d vector
////////////////////////////////////////////////////

namespace zn
{
    template< class T >
    class Vec2
    {
    public:
        T x;
        T y;
        
        Vec2( const T x = 0, const T y = 0 ) : x( x ), y( y ) {}
    };
    
    typedef Vec2< uint16 > uint16Vec2;
    typedef Vec2< int16 > int16Vec2;
    typedef Vec2< uint32 > uint32Vec2;
    typedef Vec2< int32 > int32Vec2;
    typedef Vec2< float > fVec2;
}