#pragma once
////////////////////////////////////////////////////
// quaternion
////////////////////////////////////////////////////

#include "..\Graphics\RendererType.h"

namespace zn
{
    class D3DQUATERNIONTYPE;

    template< class T >
    class Quaternion
    {
    public:
        T x, y, z, w;

        Quaternion() {};
    };

    template<>
    class Quaternion< D3DQUATERNIONTYPE > : public D3DXQUATERNION
    {
    public:
        static D3DXQUATERNION* Identity( Quaternion* quat ) { return D3DXQuaternionIdentity( quat ); }
    };

#ifdef ZN_PLATFORM_WIN32
    typedef Quaternion< D3DQUATERNIONTYPE > fQuaternion;
#else
    typedef Quaternion< float > fQuaternion;
#endif
}