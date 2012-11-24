////////////////////////////////////////////////////
// 4d vector
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Vec4.h"
#include "Vec3.h"

namespace zn
{
    template< class T >
    Vec4< T >::Vec4( const fVec3& vec ) : x( vec.x ), y( vec.y ), z( vec.z ), w( 1.f ) {}

    Vec4< D3DVECTOR4TYPE >::Vec4( const fVec3& vec ) : D3DXVECTOR4( vec.x, vec.y, vec.z, 1.f ) {}

    const Vec4< float > Vec4< float >::right( 1.f, 0.f, 0.f, 0.f );
    const Vec4< float > Vec4< float >::up( 0.f, 1.f, 0.f, 0.f );
    const Vec4< float > Vec4< float >::forward( 0.f, 0.f, 1.f, 0.f );
    const Vec4< D3DVECTOR4TYPE > Vec4< D3DVECTOR4TYPE >::right( 1.f, 0.f, 0.f, 0.f );
    const Vec4< D3DVECTOR4TYPE > Vec4< D3DVECTOR4TYPE >::up( 0.f, 1.f, 0.f, 0.f );
    const Vec4< D3DVECTOR4TYPE > Vec4< D3DVECTOR4TYPE >::forward( 0.f, 0.f, 1.f, 0.f );
}