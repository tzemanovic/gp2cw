#pragma once
////////////////////////////////////////////////////
// index buffer
////////////////////////////////////////////////////

namespace zn
{
    class IndexBuffer
    {
    public:
        IndexBuffer() 
#           ifdef ZN_PLATFORM_WIN32
                : D3D11( NULL ) 
#           endif
        {
        
        }

        ~IndexBuffer()
        {
#           ifdef ZN_PLATFORM_WIN32
                ZN_SAFE_RELEASE( D3D11 );
#           endif
        }

        union
        {
#           ifdef ZN_PLATFORM_WIN32
                ID3D11Buffer* D3D11;
#           endif
        };
    };
}