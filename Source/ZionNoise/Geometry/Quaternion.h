#pragma once
////////////////////////////////////////////////////
// quaternion
////////////////////////////////////////////////////

#include "..\Graphics\RendererType.h"

namespace zn
{
    class D3DQUATERNIONTYPE;

    template< class T >
    class QuaternionDef
    {
    public:
        T x, y, z, w;

        QuaternionDef() {};
    };

    template<>
    class QuaternionDef< D3DQUATERNIONTYPE > : public D3DXQUATERNION
    {
    public:
        QuaternionDef( const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f ) :
          D3DXQUATERNION( x, y, z, w ) 
        {
          
        }

        static D3DXQUATERNION* Identity( QuaternionDef* quat ) { return D3DXQuaternionIdentity( quat ); }
        static D3DXQUATERNION* Normalize( QuaternionDef* quat ) { return D3DXQuaternionNormalize( quat, quat ); }
    };

#ifdef ZN_PLATFORM_WIN32
    typedef QuaternionDef< D3DQUATERNIONTYPE > Quaternion;
#else
    typedef QuaternionDef< float > Quaternion;
#endif
}