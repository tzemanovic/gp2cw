////////////////////////////////////////////////////
// main function
// 
// Defined main function to be used instead of 
// WinMain on Windows.
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"

#ifdef ZN_PLATFORM_WIN32
    #include <Windows.h>

    extern int main( int argc, char** argv );

    int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, INT )
    {
        return main( __argc, __argv );
    }
#endif