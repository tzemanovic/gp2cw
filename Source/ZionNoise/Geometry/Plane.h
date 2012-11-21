#pragma once
////////////////////////////////////////////////////
// plane
////////////////////////////////////////////////////

#include "..\Graphics\RendererType.h"

namespace zn
{
#ifdef ZN_PLATFORM_WIN32

    class PlaneDefD3D : public D3DXPLANE
    {
    public:
        PlaneDefD3D() : D3DXPLANE( 0.f, 0.f, 0.f, 0.f ) {}
        PlaneDefD3D( float a, float b, float c, float d ) : D3DXPLANE( a, b, c, d ) {}

        void Init( const fVec3& p0, const fVec3& p1, const fVec3& p2 );
        void Normalize();
        bool IsInside( const fVec3& point, const float radius ) const;

        static inline float PlaneDotCoord( const PlaneDefD3D* pP, const fVec3* pV );
    };

    typedef PlaneDefD3D Plane;

#else

    class PlaneDef
    {
    public:
        float a, b, c, d;

        PlaneDef() : a( 0.f ), b( 0.f ), c( 0.f ), d( 0.f ) {}
        PlaneDef( float a, float b, float c, float d ) : a( a ), b( b ), c( c ), d( d ) {}

        void Init( const fVec3& p0, const fVec3& p1, const fVec3& p2 ) 
        { 
            // not implemented yet 
        }
        void Normalize() 
        { 
            // not implemented yet 
        }
        bool IsInside( const fVec3& point, const float radius ) const;

        static inline float PlaneDotCoord( const PlaneDef* pP, const fVec3* pV );
    };

    typedef PlaneDef Plane;

#endif
}