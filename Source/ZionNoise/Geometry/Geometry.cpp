////////////////////////////////////////////////////
// geometry functions
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"

namespace zn
{
    namespace Geometry
    {
#       ifdef ZN_PLATFORM_WIN32

        D3DXQUATERNION* QuaternionRotationMatrix( Quaternion* pQuaternion, const Mat4x4* pMat )
        {
            return D3DXQuaternionRotationMatrix( pQuaternion, pMat );
        }

        D3DXMATRIX* MatrixRotationQuaternion( Mat4x4* pMat, const Quaternion* pQuaternion )
        {
            return D3DXMatrixRotationQuaternion( pMat, pQuaternion );
        }

        D3DXMATRIX* MatrixMultiply( Mat4x4* pOut, Mat4x4* pMat1, Mat4x4* pMat2 )
        {
            return D3DXMatrixMultiply( pOut, pMat1, pMat2 );
        }

        D3DXMATRIX* MatrixTranslation( Mat4x4* pOut, const fVec3& translation )
        {
            return D3DXMatrixTranslation( pOut, translation.x, translation.y, translation.z );
        }

        D3DXMATRIX* MatrixScaling( Mat4x4* pOut, const fVec3& scale )
        {
            return D3DXMatrixScaling( pOut, scale.x, scale.y, scale.z );
        }

#       endif
    }
}