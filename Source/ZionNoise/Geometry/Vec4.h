#pragma once
////////////////////////////////////////////////////
// 4d vector
////////////////////////////////////////////////////

#include "..\Graphics\RendererType.h"

namespace zn
{
    class D3DVECTOR4TYPE;

    template< class T >
    class Vec4
    {
    public:
        T x, y, z, w;
        
        static const Vec4< T > right;
        static const Vec4< T > up;
        static const Vec4< T > forward;
        
        Vec4( const T x = 0, const T y = 0, const T z = 0, const T w = 0 ) : x( x ), y( y ), z( z ), w( w ) {}
        Vec4( const fVec3& vec );

        static inline float Vec4Dot( const Vec4< T >* vec1, const Vec4< T >* vec2 )
        {
            // not implemented yet
            return 0.f;
        }
        
        static inline Vec3< T >* Vec4Normalize( Vec4< T >* vecOut, const Vec4< T >* vecIn )
        {
            // not implemented yet
            return vecOut;
        }
        
        Vec4< T > operator + ( const Vec4< T >& vec ) const
        {
            return Vec4< T >( x + vec.x, y + vec.y, z + vec.z, 1.f );
        }
        
        Vec4< T > operator - ( const Vec4< T >& vec ) const
        {
            return Vec4< T >( x - vec.x, y - vec.y, z - vec.z, 1.f );
        }

        Vec4< T >& operator += ( const Vec4< T >& vec )
        {
            x += vec.x;
            y += vec.y;
            z += vec.z;
            return *this;
        }

        Vec4< T >& operator -= ( const Vec4< T >& vec )
        {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
            return *this;
        }

        template< class TT >
        friend inline Vec4< TT > operator * ( const float scalar, const Vec4< TT >& vec );
        template< class TT >
        friend inline Vec4< TT > operator * ( const Vec4< TT >& vec, const float scalar );
    };

    template<>
    class Vec4< D3DVECTOR4TYPE > : public D3DXVECTOR4
    {
    public:
        static const Vec4< D3DVECTOR4TYPE > right;
        static const Vec4< D3DVECTOR4TYPE > up;
        static const Vec4< D3DVECTOR4TYPE > forward;

        Vec4( const float x = 0, const float y = 0, const float z = 0, const float w = 0 ) : D3DXVECTOR4( x, y, z, w ) {}
        Vec4( const fVec3 &vec );

        static inline float Vec4Dot( const Vec4< D3DVECTOR4TYPE >* vec1, const Vec4< D3DVECTOR4TYPE >* vec2 )
        {
            return D3DXVec4Dot( vec1, vec2 );
        }
        
        static inline D3DXVECTOR4* Vec3Normalize( Vec4< D3DVECTOR4TYPE >* vecOut, const Vec4< D3DVECTOR4TYPE >* vecIn )
        {
            return D3DXVec4Normalize( vecOut, vecIn );
        }
        
        Vec4< D3DVECTOR4TYPE > operator+( const Vec4< D3DVECTOR4TYPE >& vec ) const
        {
            return Vec4< D3DVECTOR4TYPE >( x + vec.x, y + vec.y, z + vec.z, 1.f );
        }
        
        Vec4< D3DVECTOR4TYPE > operator-( const Vec4< D3DVECTOR4TYPE >& vec ) const
        {
            return Vec4< D3DVECTOR4TYPE >( x - vec.x, y - vec.y, z - vec.z, 1.f );
        }

        template< class TT >
        friend inline Vec4< TT > operator * ( const float scalar, const Vec4< TT >& vec );
        template< class TT >
        friend inline Vec4< TT > operator * ( const Vec4< TT >& vec, const float scalar );
    };
    
    template< class T >
    inline Vec4< T > operator * ( const float scalar, const Vec4< T >& vec )
    {
        return Vec4< T >( vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w );
    }

    template< class T >
    inline Vec4< T > operator * ( const Vec4< T >& vec, const float scalar )
    {
        return scalar * vec;
    }

#ifdef ZN_PLATFORM_WIN32
    typedef Vec4< D3DVECTOR4TYPE > fVec4;
#else
    typedef Vec4< float > fVec4;
#endif
}