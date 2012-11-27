#pragma once
////////////////////////////////////////////////////
// 3d vector
////////////////////////////////////////////////////

#include "..\Graphics\RendererType.h"

namespace zn
{
    class D3DVECTOR3TYPE;

    template< class T >
    class Vec3
    {
    public:
        T x, y, z;
        
        static const Vec3< T > right;
        static const Vec3< T > up;
        static const Vec3< T > forward;
        
        Vec3( const T x = 0, const T y = 0, const T z = 0 ) : x( x ), y( y ), z( z ) {}

        static inline float Vec3Dot( const Vec3< T >* vec1, const Vec3< T >* vec2 )
        {
            // not implemented yet
            return 0.f;
        }
        
        static inline Vec3< T >* Normalize( Vec3< T >* vecOut, const Vec3< T >* vecIn )
        {
            // not implemented yet
            return vecOut;
        }
        
        Vec3< T > operator + ( const Vec3< T >& vec ) const
        {
            return Vec3< T >( x + vec.x, y + vec.y, z + vec.z );
        }
        
        Vec3< T > operator - ( const Vec3< T >& vec ) const
        {
            return Vec3< T >( x - vec.x, y - vec.y, z - vec.z );
        }

        Vec3< T >& operator += ( const Vec3< T >& vec )
        {
            x += vec.x;
            y += vec.y;
            z += vec.z;
            return *this;
        }

        Vec3< T >& operator -= ( const Vec3< T >& vec )
        {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
            return *this;
        }

        template< class TT >
        friend inline Vec3< TT > operator * ( const float scalar, const Vec3< TT >& vec );
        template< class TT >
        friend inline Vec3< TT > operator * ( const Vec3< TT >& vec, const float scalar );
    };

    template<>
    class Vec3< D3DVECTOR3TYPE > : public D3DXVECTOR3
    {
    public:
        static const Vec3< D3DVECTOR3TYPE > right;
        static const Vec3< D3DVECTOR3TYPE > up;
        static const Vec3< D3DVECTOR3TYPE > forward;

        Vec3( const float x = 0, const float y = 0, const float z = 0 ) : D3DXVECTOR3( x, y, z ) {}

        static inline float Vec3Dot( const Vec3< D3DVECTOR3TYPE >* vec1, const Vec3< D3DVECTOR3TYPE >* vec2 )
        {
            return D3DXVec3Dot( vec1, vec2 );
        }
        
        static inline D3DXVECTOR3* Normalize( Vec3< D3DVECTOR3TYPE >* vecOut, const Vec3< D3DVECTOR3TYPE >* vecIn )
        {
            return D3DXVec3Normalize( vecOut, vecIn );
        }
        
        static inline D3DXVECTOR3* Normalize( Vec3< D3DVECTOR3TYPE >* vec )
        {
            return D3DXVec3Normalize( vec, vec );
        }
        
        Vec3< D3DVECTOR3TYPE > operator + ( const Vec3< D3DVECTOR3TYPE >& vec ) const
        {
            return Vec3< D3DVECTOR3TYPE >( x + vec.x, y + vec.y, z + vec.z );
        }
        
        Vec3< D3DVECTOR3TYPE > operator - ( const Vec3< D3DVECTOR3TYPE >& vec ) const
        {
            return Vec3< D3DVECTOR3TYPE >( x - vec.x, y - vec.y, z - vec.z );
        }
        
        Vec3< D3DVECTOR3TYPE > operator / ( const float scalar ) const
        {
            return Vec3< D3DVECTOR3TYPE >( x / scalar, y / scalar, z / scalar );
        }

        template< class TT >
        friend inline Vec3< TT > operator * ( const float scalar, const Vec3< TT >& vec );
        template< class TT >
        friend inline Vec3< TT > operator * ( const Vec3< TT >& vec, const float scalar );
    };
    
    template< class T >
    inline Vec3< T > operator * ( const float scalar, const Vec3< T >& vec )
    {
        return Vec3< T >( vec.x * scalar, vec.y * scalar, vec.z * scalar );
    }

    template< class T >
    inline Vec3< T > operator * ( const Vec3< T >& vec, const float scalar )
    {
        return scalar * vec;
    }

#ifdef ZN_PLATFORM_WIN32
    typedef Vec3< D3DVECTOR3TYPE > fVec3;
#else
    typedef Vec3< float > fVec3;
#endif
}