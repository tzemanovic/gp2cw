////////////////////////////////////////////////////
// plane
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Plane.h"
#include "Vec3.h"

namespace zn
{
#ifdef ZN_PLATFORM_WIN32

    void PlaneDefD3D::Init( const fVec3& p0, const fVec3& p1, const fVec3& p2 )
    {
        D3DXPlaneFromPoints( this, &p0, &p1, &p2 );
        Normalize();
    }

    void PlaneDefD3D::Normalize()
    {
        float mag;
	    mag = sqrt( a * a + b * b + c * c );
	    a = a / mag;
	    b = b / mag;
	    c = c / mag;
	    d = d / mag;
    }

    bool PlaneDefD3D::IsInside( const fVec3& point, const float radius ) const
    {
        float distance;
	    distance = PlaneDefD3D::PlaneDotCoord( this, &point );	
	    return distance >= -radius;
    }

    float PlaneDefD3D::PlaneDotCoord( const PlaneDefD3D* pP, const fVec3* pV )
    {
        return D3DXPlaneDotCoord( pP, pV );
    }

#else

    bool PlaneDef::IsInside( const fVec3& point, const float radius ) const
    {
        float distance;
	    distance = PlaneDef::PlaneDotCoord( this, &point );	
	    return distance >= -radius;
    }

    float PlaneDef::PlaneDotCoord( const PlaneDef* pP, const fVec3* pV )
    {
        return pP->a * pV->x + pP->b * pV->y + pP->c * pV->z + pP->d;
    }

#endif
}