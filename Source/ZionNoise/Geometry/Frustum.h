#pragma once
////////////////////////////////////////////////////
// view frustrum
////////////////////////////////////////////////////

#include "Plane.h"

namespace zn
{
    namespace FrustumSides
    {
        enum { Near, Far, Top, Right, Bottom, Left, Count };
    }

    class Frustum
    {
    public:
	    Frustum();
        void Init( float fieldOfView, float aspectRatio, float nearClipDist, float farClipDist );
        bool IsInside( const fVec3& point, const float radius ) const;

        const float GetFieldOfView() const { return m_fieldOfView; }
        const float GetAspectRatio() const { return m_aspectRatio; }
        void SetAspectRatio( const float aspectRatio ) { m_aspectRatio = aspectRatio; }
        const float GetNearClipDist() const { return m_nearClipDist; }
        const float GetFarClipDist() const { return m_farClipDist; }

    private:
        Plane m_planes[FrustumSides::Count];
	    fVec3 m_nearClipVerts[4];
	    fVec3 m_farClipVerts[4];
	    float m_fieldOfView; // radians
	    float m_aspectRatio; // width / height
	    float m_nearClipDist;
	    float m_farClipDist;
    };
}