#pragma once
////////////////////////////////////////////////////
// matrix 4x4
////////////////////////////////////////////////////

#include "Vec3.h"
#include "Vec4.h"

namespace zn
{
    class Mat4x4Def
    {
    public:
        union 
        {
            struct 
            {
                float _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44;

            };
           float m[4][4];
        };

        Mat4x4Def() {}
        Mat4x4Def( float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, 
            float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44 ) 
            : _11( m11 ), _12( m12 ), _13( m13 ), _14( m14 ), _21( m21 ), _22( m22 ), _23( m23 ), _24( m24 ), 
            _31( m31 ), _32( m32 ), _33( m33 ), _34( m34 ), _41( m41 ), _42( m42 ), _43( m43 ), _44( m44 )
        {

        }

        static const Mat4x4Def identity;

        static inline Mat4x4Def* Identity( Mat4x4Def* mat ) 
        {
            // not implemented yet
            return &Mat4x4Def();
        }
        
        inline Mat4x4Def Inverse() const
        {
            // not implemented yet
            return Mat4x4Def();
        }
        
        inline const fVec3 GetPosition() const { return fVec3( m[3][0], m[3][1], m[3][2] ); }
        inline void SetPosition( const fVec3 pos ) { m[3][0] = pos.x, m[3][1] = pos.y; m[3][2] = pos.z; m[3][3] = 1.0f; }
    };

    class Mat4x4DefD3D : public D3DXMATRIX
    {
    public:
        Mat4x4DefD3D() : D3DXMATRIX() {}
        Mat4x4DefD3D( float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, 
            float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44 ) 
            : D3DXMATRIX( m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44 )
        {

        }

        static const Mat4x4DefD3D identity;

        Mat4x4DefD3D operator*( const Mat4x4DefD3D& mat ) const
        {
            Mat4x4DefD3D out;
            D3DXMatrixMultiply(&out, this, &mat);
            return out;
        }

        static inline D3DXMATRIX* Identity( Mat4x4DefD3D* mat ) { return D3DXMatrixIdentity( mat ); }

        inline Mat4x4DefD3D Inverse() const
        {
            Mat4x4DefD3D inverse;
	        D3DXMatrixInverse( &inverse, NULL, this );
	        return inverse;
        }

        inline const fVec3 GetPosition() const 
        { 
            return fVec3( m[3][0], m[3][1], m[3][2] ); 
        }

        inline void SetPosition( const fVec3 pos ) 
        { 
            m[3][0] = pos.x, m[3][1] = pos.y; m[3][2] = pos.z; m[3][3] = 1.0f; 
        }
        
        inline fVec3 Transform( fVec3& v ) const
        {
            fVec4 out, temp( v );
            D3DXVec4Transform( &out, &temp, this );
            return fVec3( out.x, out.y, out.z );
        }

        inline fVec4 Transform( fVec4& v ) const
        {
            fVec4 out;
            D3DXVec4Transform( &out, &v, this );
            return out;
        }

        inline void BuildYawPitchRoll( const float yawRadians, const float pitchRadians, const float rollRadians )
		{ 
            D3DXMatrixRotationYawPitchRoll( this, yawRadians, pitchRadians, rollRadians ); 
        }
    };

#ifdef ZN_PLATFORM_WIN32
    typedef Mat4x4DefD3D Mat4x4;
#else
    typedef Mat4x4Def Mat4x4;
#endif
}