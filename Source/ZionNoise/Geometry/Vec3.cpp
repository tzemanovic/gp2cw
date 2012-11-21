////////////////////////////////////////////////////
// 3d vector
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Vec3.h"

namespace zn
{
    const Vec3< float > Vec3< float >::right( 1.f, 0.f, 0.f );
    const Vec3< float > Vec3< float >::up( 0.f, 1.f, 0.f );
    const Vec3< float > Vec3< float >::forward( 0.f, 0.f, 1.f );
    const Vec3< D3DVECTOR3TYPE > Vec3< D3DVECTOR3TYPE >::right( 1.f, 0.f, 0.f );
    const Vec3< D3DVECTOR3TYPE > Vec3< D3DVECTOR3TYPE >::up( 0.f, 1.f, 0.f );
    const Vec3< D3DVECTOR3TYPE > Vec3< D3DVECTOR3TYPE >::forward( 0.f, 0.f, 1.f );
}