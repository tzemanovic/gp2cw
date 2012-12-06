////////////////////////////////////////////////////
// geometry functions
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"

namespace zn
{
    namespace Geometry
    {
#       ifdef ZN_PLATFORM_WIN32

        D3DXVECTOR3* Vec3Cross( fVec3* pOut, const fVec3* pV1, const fVec3* pV2 )
        {
            return D3DXVec3Cross( pOut, pV1, pV2 );
        }

        D3DXQUATERNION* QuaternionRotationMatrix( Quaternion* pQuaternion, const Mat4x4* pMat )
        {
            return D3DXQuaternionRotationMatrix( pQuaternion, pMat );
        }

        D3DXQUATERNION* QuaternionRotationVectorRad( Quaternion* pQuaternion, const fVec3& vec )
        {
            return D3DXQuaternionRotationYawPitchRoll( pQuaternion, vec.y, vec.x, vec.z );
        }

        D3DXQUATERNION* QuaternionRotationVectorDeg( Quaternion* pQuaternion, const fVec3& vec )
        {
            return D3DXQuaternionRotationYawPitchRoll( pQuaternion, Math::DegreesToRadians( vec.y ), 
                Math::DegreesToRadians( vec.x ), Math::DegreesToRadians( vec.z ) );
        }

        D3DXQUATERNION* QuaternionRotationAxis( Quaternion* pOut, const fVec3& axis, const float angle )
        {
            return D3DXQuaternionRotationAxis( pOut, &axis, angle );
        }

        D3DXMATRIX* MatrixRotationQuaternion( Mat4x4* pMat, const Quaternion* pQuaternion )
        {
            return D3DXMatrixRotationQuaternion( pMat, pQuaternion );
        }

        D3DXMATRIX* MatrixMultiply( Mat4x4* pOut, const Mat4x4* pMat1, const Mat4x4* pMat2 )
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

        D3DXMATRIX* MatrixLookAtLH( Mat4x4* pOut, const fVec3& eye, const fVec3& target, const fVec3& up )
        {
            return D3DXMatrixLookAtLH( pOut, &eye, &target, &up );
        }

#       endif
    }
}