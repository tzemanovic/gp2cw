#pragma once
////////////////////////////////////////////////////
// rendering device
////////////////////////////////////////////////////

namespace zn
{
    class Device
    {
    public:
        Device() 
#           ifdef ZN_PLATFORM_WIN32
                : D3D11( NULL ) 
#           endif
        {
        
        }

        ~Device()
        {
#           ifdef ZN_PLATFORM_WIN32
                ZN_SAFE_RELEASE( D3D11 );
#           endif
        }

        union
        {
#           ifdef ZN_PLATFORM_WIN32
                ID3D11Device* D3D11;
#           endif
        };
    };
}