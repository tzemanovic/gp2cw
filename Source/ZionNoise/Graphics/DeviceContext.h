#pragma once
////////////////////////////////////////////////////
// rendering device context
////////////////////////////////////////////////////

namespace zn
{
    class DeviceContext
    {
    public:
        DeviceContext() 
#           ifdef ZN_PLATFORM_WIN32
                : D3D11( NULL ) 
#           endif
        {
        
        }

        ~DeviceContext()
        {
#           ifdef ZN_PLATFORM_WIN32
                ZN_SAFE_RELEASE( D3D11 );
#           endif
        }

        union
        {
#           ifdef ZN_PLATFORM_WIN32
                ID3D11DeviceContext* D3D11;
#           endif
        };
    };
}