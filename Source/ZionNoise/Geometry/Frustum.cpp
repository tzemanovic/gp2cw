////////////////////////////////////////////////////
// view frustrum
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Frustum.h"

namespace zn
{
    Frustum::Frustum()
    {

    }

    void Frustum::Init( float fieldOfView, float aspectRatio, float nearClipDist, float farClipDist )
    {
        m_fieldOfView = fieldOfView;
        m_aspectRatio = aspectRatio;
        m_nearClipDist = nearClipDist;
        m_farClipDist = farClipDist;

        float tanHalfFov = tan( m_fieldOfView / 2.f );
        fVec3 nearRight = ( m_nearClipDist * tanHalfFov ) * m_aspectRatio * fVec3::right;
        fVec3 farRight = ( m_farClipDist * tanHalfFov ) * m_aspectRatio * fVec3::right;
        fVec3 nearUp = ( m_nearClipDist * tanHalfFov ) * m_aspectRatio * fVec3::up;
        fVec3 farUp = ( m_farClipDist * tanHalfFov ) * m_aspectRatio * fVec3::up;
        
        m_nearClipVerts[0] = ( m_nearClipDist * fVec3::forward ) - nearRight + nearUp;
        m_nearClipVerts[1] = ( m_nearClipDist * fVec3::forward ) + nearRight + nearUp;
        m_nearClipVerts[2] = ( m_nearClipDist * fVec3::forward ) + nearRight - nearUp;
        m_nearClipVerts[3] = ( m_nearClipDist * fVec3::forward ) - nearRight - nearUp;

        m_farClipVerts[0] = ( m_farClipDist * fVec3::forward ) - farRight + farUp;
        m_farClipVerts[1] = ( m_farClipDist * fVec3::forward ) + farRight + farUp;
        m_farClipVerts[2] = ( m_farClipDist * fVec3::forward ) + farRight - farUp;
        m_farClipVerts[3] = ( m_farClipDist * fVec3::forward ) - farRight - farUp;

        fVec3 origin;
        m_planes[FrustumSides::Near].Init( m_nearClipVerts[2], m_nearClipVerts[1], m_nearClipVerts[0] );
        m_planes[FrustumSides::Far].Init( m_farClipVerts[0], m_farClipVerts[1], m_farClipVerts[2] );
        m_planes[FrustumSides::Right].Init( m_farClipVerts[2], m_farClipVerts[1], origin );
        m_planes[FrustumSides::Top].Init( m_farClipVerts[1], m_farClipVerts[0], origin );
        m_planes[FrustumSides::Left].Init( m_farClipVerts[0], m_farClipVerts[3], origin );
        m_planes[FrustumSides::Bottom].Init( m_farClipVerts[3], m_farClipVerts[2], origin );
    }

    bool Frustum::IsInside( const fVec3& point, const float radius ) const
    {
        for( int i = 0; i < FrustumSides::Count; ++i ) 
	    {	
		    if( !m_planes[i].IsInside( point, radius ) )
            {
			    return false;
            }
	    }	
	    return true;
    }
}