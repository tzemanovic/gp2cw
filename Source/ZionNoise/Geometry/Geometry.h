#pragma once
////////////////////////////////////////////////////
// geometry functions
////////////////////////////////////////////////////

#include "..\Geometry\Vec2.h"
#include "..\Geometry\Vec3.h"
#include "..\Geometry\Vec4.h"
#include "..\Geometry\Mat4x4.h"
#include "..\Geometry\Quaternion.h"
#include "..\Geometry\Vertex.h"
#include "..\Geometry\Color.h"
#include "..\Geometry\Vertex.h"
#include "..\Geometry\Frustum.h"
#include "..\Geometry\Plane.h"

namespace zn
{
    namespace Geometry
    {
#       ifdef ZN_PLATFORM_WIN32

        D3DXQUATERNION* QuaternionRotationMatrix( Quaternion* pQuaternion, const Mat4x4* pMat );
        D3DXMATRIX* MatrixRotationQuaternion( Mat4x4* pMat, const Quaternion* pQuaternion );
        D3DXMATRIX* MatrixMultiply( Mat4x4* pOut, Mat4x4* pMat1, Mat4x4* pMat2 );
        D3DXMATRIX* MatrixTranslation( Mat4x4* pOut, const fVec3& translation );
        D3DXMATRIX* MatrixScaling( Mat4x4* pOut, const fVec3& scale );

#       endif
    }
}