////////////////////////////////////////////////////
// matrix 4x4
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Mat4x4.h"
#include "Quaternion.h"

namespace zn
{
    const Mat4x4Def Mat4x4Def::identity( Mat4x4Def( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
    const Mat4x4DefD3D Mat4x4DefD3D::identity( Mat4x4DefD3D( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
}